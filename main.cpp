#include "iqplayer.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IQPlayer w;
    QFile fileReader(":/style.css");
    fileReader.open(QIODevice::ReadOnly);
    a.setStyleSheet(fileReader.readAll());
    fileReader.close();
    w.setStyleSheet("QWidget");
    w.show();
    return a.exec();
}
