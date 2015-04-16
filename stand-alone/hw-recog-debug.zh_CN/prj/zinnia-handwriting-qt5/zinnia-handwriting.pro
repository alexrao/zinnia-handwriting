##
# prj/zinnia-handwriting-qt5/zinnia-handwriting.pro
# NOTE: please use "release", NOT debug

QT += gui widgets

TARGET = hw-recog-debug.zh_CN

TEMPLATE = app


## CXXFLAGS
QMAKE_CXXFLAGS_RELEASE += -I../../../../include
QMAKE_CXXFLAGS_RELEASE += -DMINGW32=1
QMAKE_CXXFLAGS_RELEASE += -DID_QT_VERSION=0x050401

## LDFLAGS
LIBS += ../../../../zinnia/lib/libzinnia.lib


## SRC
SOURCES += \
	../../main.cpp \
    ../../handwritor.cpp \
    ../../handwritor_debug.cpp


## MOC H
HEADERS += \
    ../../handwritor.h \
    ../../handwritor_debug.h
