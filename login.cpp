#include "login.h"
#include "QDebug"
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // QRect parentGeometry = parent->geometry();
    // qDebug() <<  "Parent: " << parentGeometry;
    // this->setGeometry(0, 0, parentGeometry.width(), parentGeometry.height());
    // qDebug() << "Login: " << this->geometry();

}

Login::~Login()
{
    delete ui;
}

void Login::on_bt_login_clicked()
{
    emit loginSuccess();
}

