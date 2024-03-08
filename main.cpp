#include "widget.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QFile file("./theme/style.qss");
    try {
        if (!file.open(QFile::ReadOnly)) {
            throw QString("Cannot open file: ") + file.errorString();
        }

        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
    } catch (const QString &error) {
        qCritical() << error;
        // You can add further error handling here if needed
        // For example, exit the application:
        return -1;
    }

    w.showMaximized();
    return a.exec();
}
