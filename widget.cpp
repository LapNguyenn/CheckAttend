#include "widget.h"
#include "./ui_widget.h"
#include <QToolButton>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    openLoginPage();

}

void Widget::openLoginPage()
{
    if (loginActivity) {
        delete loginActivity;
    }
    loginActivity = new Login(this);
    int loginPageIndex = ui->stackedWidget->indexOf(ui->page_login);
    ui->stackedWidget->removeWidget(ui->page_login);
    ui->stackedWidget->insertWidget(loginPageIndex, loginActivity);
    ui->stackedWidget->setCurrentIndex(loginPageIndex);

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
    if(loginActivity){
        delete loginActivity;
    }
}

