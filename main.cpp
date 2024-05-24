#include "widget.h"
#include <QApplication>
#include <QLocale>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Phần mềm điểm danh");
    w.showMaximized();
    return a.exec();
}
