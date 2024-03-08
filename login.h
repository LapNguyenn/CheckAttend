#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QWidget>
#include "ui_login.h"

class Login : public QWidget
{
    Q_OBJECT
public:
    Login(QWidget *parent = nullptr);
    ~Login();
signals:
    void loginSuccess();
private slots:
    void on_bt_login_clicked();
private:
    Ui::Form *ui;
};

#endif // LOGIN_H
