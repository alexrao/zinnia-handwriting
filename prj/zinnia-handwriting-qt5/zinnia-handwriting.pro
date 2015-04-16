##
# prj/zinnia-handwriting-qt5/zinnia-handwriting.pro
# NOTE: please use "release", NOT debug

QT += gui widgets

TARGET = zinnia-handwriting

TEMPLATE = app


## CXXFLAGS
QMAKE_CXXFLAGS_RELEASE += -I../../include
QMAKE_CXXFLAGS_RELEASE += -DMINGW32=1
QMAKE_CXXFLAGS_RELEASE += -DID_QT_VERSION=0x050401

## LDFLAGS
LIBS += ../../zinnia/lib/libzinnia.lib


## SRC
# ../../zinnia/libzinnia.cpp # current msw NOT need this
SOURCES += ../../main.cpp \
    ../../handwritor.cpp


## MOC H
HEADERS += \
    ../../include/handwritor.h
