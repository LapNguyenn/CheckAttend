#include "login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{

}

Login::~Login()
{
    delete ui;
}

void Login::on_bt_login_clicked()
{
    emit loginSuccess();
}

