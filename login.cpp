#include "login.h"
#include "QDebug"
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Login::~Login()
{
    delete ui;
}

void Login::on_bt_login_clicked()
{
    emit loginSuccess();
}

