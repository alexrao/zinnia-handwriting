/*
 * mmap.h
 */


#ifndef zinnia_MMAP_H_
#define zinnia_MMAP_H_

#include <errno.h>
#include <string>
#include <sstream>

#if defined(MINGW32)
# include <windows.h>
#endif /* defined(MINGW32) */


#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

extern "C" {
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif

#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif

#include <string.h>
} /* "C" */

#include "common.h"


namespace {
int open__(const char* name, int flag) { return open(name, flag); }
int close__(int fd) { return close(fd); }
}

namespace zinnia {

template <class T> class Mmap {
 private:
  T            *text;
  size_t       length;
  std::string  fileName;
  whatlog what_;

#if defined(MINGW32)
  HANDLE hFile;
  HANDLE hMap;
#else
# error "NOT support"
#endif /* defined(MINGW32) */

 public:
  T&       operator[](size_t n)       { return *(text + n); }
  const T& operator[](size_t n) const { return *(text + n); }
  T*       begin()           { return text; }
  const T* begin()    const  { return text; }
  T*       end()           { return text + size(); }
  const T* end()    const  { return text + size(); }
  size_t size()               { return length/sizeof(T); }
  const char *what()          { return what_.str(); }
  const char *file_name()     { return fileName.c_str(); }
  size_t file_size()          { return length; }
  bool empty()                { return(length == 0); }


  // This code is imported from sufary, develoved by
  //  TATUO Yamashita <yto@nais.to> Thanks!
#if defined(MINGW32)
  bool open(const char *filename, const char *mode = "r") {
    this->close();
    unsigned long mode1, mode2, mode3;
    fileName = std::string(filename);

    if (std::strcmp(mode, "r") == 0) {
      mode1 = GENERIC_READ;
      mode2 = PAGE_READONLY;
      mode3 = FILE_MAP_READ;
    } else if (std::strcmp(mode, "r+") == 0) {
      mode1 = GENERIC_READ | GENERIC_WRITE;
      mode2 = PAGE_READWRITE;
      mode3 = FILE_MAP_ALL_ACCESS;
    } else {
      CHECK_CLOSE_FALSE(false) << "unknown open mode:" << filename;
    }

	wstringstream wc_filename;
	wc_filename << filename;
    hFile = CreateFile(wc_filename.str().c_str(), mode1, FILE_SHARE_READ, 0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
    CHECK_CLOSE_FALSE(hFile != INVALID_HANDLE_VALUE)
        << "CreateFile() failed: " << filename;

    length = GetFileSize(hFile, 0);

    hMap = CreateFileMapping(hFile, 0, mode2, 0, 0, 0);
    CHECK_CLOSE_FALSE(hMap) << "CreateFileMapping() failed: " << filename;

    text = reinterpret_cast<T *>(MapViewOfFile(hMap, mode3, 0, 0, 0));
    CHECK_CLOSE_FALSE(text) << "MapViewOfFile() failed: " << filename;

    return true;
  }

  void close() {
    if (text) { UnmapViewOfFile(text); }
    if (hFile != INVALID_HANDLE_VALUE) {
      CloseHandle(hFile);
      hFile = INVALID_HANDLE_VALUE;
    }
    if (hMap) {
      CloseHandle(hMap);
      hMap = 0;
    }
    text = 0;
  }

  Mmap(): text(0), hFile(INVALID_HANDLE_VALUE), hMap(0) {}

#else
# error "NOT SUPPORT"
#endif /* defined(MINGW32) */

  virtual ~Mmap() { this->close(); }
};
}
#endif
