# -------------------------------------------------
# Project created by QtCreator 2011-03-09T20:14:56
# -------------------------------------------------
QT += gui
TARGET = zinnia
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    trainer.cpp \
    svm.cpp \
    sexp.cpp \
    recognizer.cpp \
    param.cpp \
    libzinnia.cpp \
    feature.cpp \
    character.cpp \
    QHWR.cpp
HEADERS += zinnia.h \
    svm.h \
    sexp.h \
    scoped_ptr.h \
    param.h \
    mmap.h \
    feature.h \
    config.h \
    common.h \
    stream_wrapper.h \
    freelist.h \
    QHWR.h
