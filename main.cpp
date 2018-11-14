#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    MainWindow w;
    w.show();
    return a.exec();
}
