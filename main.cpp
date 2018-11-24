#include "mainwindow.h"
#include <QApplication>
#include "stdlib.h"  /* system lib */
#include "stdio.h"
#include "unistd.h"
#include "iostream"
#include "string"
#include "thread"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
