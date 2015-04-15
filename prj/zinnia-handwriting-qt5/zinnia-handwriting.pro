TARGET = zinnia-handwriting.pro

TEMPLATE = app


##
QMAKE_CXXFLAGS_RELEASE += -I../../include
QMAKE_CXXFLAGS_RELEASE += -DMINGW32=1
QMAKE_CXXFLAGS_RELEASE += -DID_QT_VERSION=0x050401


##
SOURCES += ../../main.cpp \
    ../../zinnia/libzinnia.cpp


##
HEADERS += ../../zinnia/common.h \
	../../zinnia/feature.h \
	../../zinnia/freelist.h \
	../../zinnia/mmap.h \
	../../zinnia/param.h \
	../../zinnia/scoped_ptr.h \
	../../zinnia/sexp.h \
	../../zinnia/stream_wrapper.h \
	../../zinnia/svm.h \
	../../zinnia/zinnia.h
