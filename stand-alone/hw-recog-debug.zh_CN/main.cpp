/*
 * main.cpp
 */


#if !defined(ID_QT_VERSION)
#	error "ID_QT_VERSION NOT defined"
#endif

#include <QtCore/QTextCodec>
#include <QtCore/QDebug>
#if (ID_QT_VERSION < 0x050000)
#	include <QtGui/QApplication>
#else
#	include <QtWidgets/QApplication>
#endif

#include "handwritor_debug.h"


int main (int argc, char *argv[]) {
	fprintf(stderr, "%s +%d: %s\n", __FILE__, __LINE__, __func__);
	fflush(stderr);
    QApplication a(argc, argv);

	fprintf(stderr, "%s +%d: %s\n", __FILE__, __LINE__, __func__);
	fflush(stderr);

    handwritor_debug hw;
	fprintf(stderr, "%s +%d: %s\n", __FILE__, __LINE__, __func__);
	fflush(stderr);
    // hw.setGeometry(200, 200, 300, 300);
    hw.show();

    return a.exec();
} /* main */


/*
 * main.cpp
 */
