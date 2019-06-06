#include "mainpage.h"
#include <QApplication>

// Steve Jobs is Here!
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPage w;
    w.show();

    return a.exec();
}
