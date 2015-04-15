#include <QApplication>
#include <iostream>
#include "QHWR.h"
#include "zinnia.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QHWR w;
    w.setGeometry(200,200,300,300);
    w.show();
    return a.exec();
}
