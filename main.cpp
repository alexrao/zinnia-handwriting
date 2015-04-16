/*
 * main.cpp
 */


#if !defined(ID_QT_VERSION)
#	error "ID_QT_VERSION NOT defined"
#endif

#include <QtCore/QTextCodec>
#if (ID_QT_VERSION < 0x050000)
#	include <QtGui/QApplication>
#else
#	include <QtWidgets/QApplication>
#endif

#include "handwritor.h" /* the hand-writing ui panel */


int main (int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if (ID_QT_VERSION < 0x050000)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
#	endif

    handwritor hw;
    hw.setGeometry(200, 200, 300, 300);
    hw.show();

    return a.exec();
} /* main */


/*
 * main.cpp
 */
