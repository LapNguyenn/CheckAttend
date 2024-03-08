#include "widget.h"
#include "./ui_widget.h"
#include <QToolButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    openLoginPage();

}

void Widget::openLoginPage()
{
    ui->stackedWidget->setCurrentIndex(0);
    loginActivity = new Login(this);
    Ui::Form loginUi;
    loginUi.setupUi(loginActivity);
    QVBoxLayout *loginLayout = new QVBoxLayout();
    loginLayout->addWidget(loginActivity);
    ui->loginWidget->setLayout(loginLayout);
    connect(loginActivity, &Login::loginSuccess, this, [this](){
        openMainPage();
    });
}

void Widget::openMainPage()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->sideBar->setVisible(true);
    ui->body->setCurrentIndex(0);
    connect(ui->bt_sideBar, &QToolButton::clicked,this, [&](){
        if(ui->sideBar->isVisible()){
            ui->sideBar->setVisible(false);
        } else {
            ui->sideBar->setVisible(true);
        }

    });
    connect(ui->bt_open_attend_check, &QPushButton::clicked, this, [&](){
        ui->body->setCurrentIndex(0);
    });
    connect(ui->bt_open_page_schedule, &QPushButton::clicked, this, [&](){
        ui->body->setCurrentIndex(1);
    });
    connect(ui->bt_open_page_admin, &QPushButton::clicked, this, [&](){
        ui->body->setCurrentIndex(2);
    });
}


Widget::~Widget()
{
    delete ui;
}

