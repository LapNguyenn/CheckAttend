#ifndef MYDATETIME_H
#define MYDATETIME_H
#include <QDateTime>
#include <QTimeZone>
class MyDateTime {
public:
    static MyDateTime& getInstance() {
        static MyDateTime instance;
        return instance;
    }
    QString getTime() {
        currentTime = QDateTime::currentDateTime();
        currentTime.setTimeZone(QTimeZone("Asia/Ho_Chi_Minh"));
        return currentTime.toString("yyyy-MM-dd+hh:mm:ss");
    }
private:
    MyDateTime() {}
    QDateTime currentTime;
};
#endif // MYDATETIME_H
