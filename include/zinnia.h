//
//  Zinnia: Online hand recognition system with machine learning
//
//  $Id: zinnia.h 17 2009-04-05 11:40:32Z taku-ku $;
//
//  Copyright(C) 2008 Taku Kudo <taku@chasen.org>
//
#ifndef ZINNIA_H_
#define ZINNIA_H_

/* C interface  */
#ifdef __cplusplus
#include <cstdio>
#else
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SWIG
  typedef struct zinnia_character_t zinnia_character_t;
  typedef struct zinnia_recognizer_t zinnia_recognizer_t;
  typedef struct zinnia_result_t zinnia_result_t;
  typedef struct zinnia_trainer_t zinnia_trainer_t;

  /* C interface */
  extern int zinnia_do(int argc, char **argv);
  extern int zinnia_learn(int argc, char **argv);
  extern int zinnia_convert(int argc, char **argv);
  extern const char* zinnia_version();

  /* character */
  extern zinnia_character_t*  zinnia_character_new();
  extern void        zinnia_character_destroy(zinnia_character_t *character);
  extern void        zinnia_character_set_value(zinnia_character_t *character, const char *str);
  extern void        zinnia_character_set_value2(zinnia_character_t *character, const char *str, size_t length);
  extern const char *zinnia_character_value(zinnia_character_t *character);
  extern void        zinnia_character_set_width(zinnia_character_t *character, size_t width);
  extern void        zinnia_character_set_height(zinnia_character_t *character, size_t height);
  extern size_t      zinnia_character_width(zinnia_character_t *character);
  extern size_t      zinnia_character_height(zinnia_character_t *character);
  extern void        zinnia_character_clear(zinnia_character_t *stroke);
  extern int         zinnia_character_add(zinnia_character_t *character, size_t id, int x, int y);
  extern size_t      zinnia_character_strokes_size(zinnia_character_t *character);
  extern size_t      zinnia_character_stroke_size(zinnia_character_t *character, size_t id);
  extern int         zinnia_character_x(zinnia_character_t *character, size_t id, size_t i);
  extern int         zinnia_character_y(zinnia_character_t *character, size_t id, size_t i);
  extern int         zinnia_character_parse(zinnia_character_t *character, const char *str);
  extern int         zinnia_character_parse2(zinnia_character_t *character, const char *str, size_t length);
  extern int         zinnia_character_to_string(zinnia_character_t *character, char *buf, size_t length);
  extern const char* zinnia_character_strerror(zinnia_character_t *character);

  /* Recognizer::Result */
  extern const char *zinnia_result_value(zinnia_result_t *result, size_t i);
  extern float       zinnia_result_score(zinnia_result_t *result, size_t i);
  extern size_t      zinnia_result_size(zinnia_result_t *result);
  extern void        zinnia_result_destroy(zinnia_result_t *result);

  /* Recognizer */
  extern zinnia_recognizer_t *zinnia_recognizer_new();
  extern void                zinnia_recognizer_destroy(zinnia_recognizer_t *recognizer);
  extern int                 zinnia_recognizer_open(zinnia_recognizer_t *recognizer, const char *filename);
  extern int                 zinnia_recognizer_open_from_ptr(zinnia_recognizer_t *recognizer,
                                                                        const char *ptr, size_t size);
  extern int                 zinnia_recognizer_close(zinnia_recognizer_t *recognizer);
  extern size_t              zinnia_recognizer_size(zinnia_recognizer_t *recognizer);
  extern const char         *zinnia_recognizer_value(zinnia_recognizer_t *recognizer, size_t i);
  extern const char*         zinnia_recognizer_strerror(zinnia_recognizer_t *recognizer);
  extern zinnia_result_t *zinnia_recognizer_classify(zinnia_recognizer_t *recognizer,
                                                                const zinnia_character_t *character,
                                                                size_t nbest);

  /* Trainer */
  extern zinnia_trainer_t *zinnia_trainer_new();
  extern void             zinnia_trainer_destroy(zinnia_trainer_t *trainer);
  extern int              zinnia_trainer_add(zinnia_trainer_t *trainer, const zinnia_character_t* character);
  extern void             zinnia_trainer_clear(zinnia_trainer_t *trainer);
  extern int              zinnia_trainer_train(zinnia_trainer_t *trainer, const char *filename);
  extern const char      *zinnia_trainer_strerror(zinnia_trainer_t *trainer);
  extern int              zinnia_trainer_convert_model(const char *txt_model,
                                                                  const char *binary_model,
                                                                  double compression_threshold);
  extern int              zinnia_trainer_make_header(const char *txt_model,
	const char *header_file,
	const char *name,
	double compression_threshold);

#endif

#ifdef __cplusplus
}
#endif

/* C++ interface */
#ifdef __cplusplus

namespace zinnia {

const char *version(void);


class Character {
 public:
#ifndef SWIG
  virtual void set_value(const char *str, size_t length) = 0;
#endif
  virtual void set_value(const char *str) = 0;
  virtual const char *value() const = 0;
  virtual void set_width(size_t width) = 0;
  virtual void set_height(size_t height) = 0;
  virtual size_t width() const = 0;
  virtual size_t height() const = 0;
  virtual void clear() = 0;
  virtual bool add(size_t id, int x, int y) = 0;
  virtual size_t strokes_size() const = 0;
  virtual size_t stroke_size(size_t id) const = 0;
  virtual int x(size_t id, size_t i) const = 0;
  virtual int y(size_t id, size_t i) const = 0;
  virtual bool parse(const char *str) = 0;
  virtual const char *what() = 0;
#ifndef SWIG
  virtual bool parse(const char *str, size_t length) = 0;
  virtual bool toString(char *buf, size_t length) const = 0;
  static Character *create();
#endif
  virtual ~Character() {}
};

class Result {
 public:
  virtual const char *value(size_t i) const = 0;
  virtual float score(size_t i) const = 0;
  virtual size_t size() const = 0;
  virtual ~Result() {}
};

class Recognizer {
 public:
  virtual bool open(const char *filename) = 0;
  virtual bool open(const char *ptr, size_t size) = 0;
  virtual bool close() = 0;
  virtual size_t size() const = 0;
  virtual const char *value(size_t i) const = 0;
  virtual Result *classify(const Character &character, size_t nbest) const = 0;
  virtual const char *what() = 0;
  virtual ~Recognizer() {}
#ifndef SWIG
  static Recognizer* create();
#endif
};

class Trainer {
 public:
  virtual bool add(const Character &character) = 0;
  virtual void clear() = 0;
  virtual bool train(const char *filename) = 0;
  static bool convert(const char *txt_model,
                      const char *binary_model,
                      double compression_threshold);
  static bool makeHeader(const char *txt_model,
                         const char *header_file,
                         const char *name,
                         double compression_threshold);
  virtual const char *what() = 0;
  virtual ~Trainer() {}
#ifndef SWIG
  static Trainer* create();
#endif
};

#ifndef SWIG
extern Recognizer* createRecognizer();
extern Character*  createCharacter();
extern Trainer*    createTrainer();
#endif
}

#endif
#endif
