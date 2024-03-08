#include "login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
}

Login::~Login()
{

}
