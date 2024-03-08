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
private:
    Ui::Form *ui;
};

#endif // LOGIN_H
