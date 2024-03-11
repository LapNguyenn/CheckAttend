#include "widget.h"
#include "./ui_widget.h"
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
    if (!loginActivity) {
        loginActivity = new Login(this);
    }
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
    //Open check-attend page first
    openCheckAttendPage();
    //Init button click function
    connect(ui->bt_sideBar, &QPushButton::clicked,this, [&, this](){
        if(ui->sideBar->isVisible()){
            ui->sideBar->setVisible(false);
        } else {
            ui->sideBar->setVisible(true);
        }
    });
    connect(ui->bt_open_attend_check, &QPushButton::clicked, this, [&](){
        openCheckAttendPage();
    });
    connect(ui->bt_open_page_schedule, &QPushButton::clicked, this, [&](){
        ui->body->setCurrentIndex(1);
        ui->l_name_page->setText(ui->bt_open_page_schedule->text());
        ui->bt_open_attend_check->setChecked(false);
        ui->bt_open_page_schedule->setChecked(true);
        ui->bt_open_page_admin->setChecked(false);

    });
    connect(ui->bt_open_page_admin, &QPushButton::clicked, this, [&](){
        ui->body->setCurrentIndex(2);
        ui->l_name_page->setText(ui->bt_open_page_admin->text());
        ui->bt_open_attend_check->setChecked(false);
        ui->bt_open_page_schedule->setChecked(false);
        ui->bt_open_page_admin->setChecked(true);
    });
}

void Widget::openCheckAttendPage()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->body->setCurrentIndex(0);
    ui->l_name_page->setText(ui->bt_open_attend_check->text());
    ui->bt_open_attend_check->setChecked(true);
    ui->bt_open_page_schedule->setChecked(false);
    ui->bt_open_page_admin->setChecked(false);
    if(!checkAttendActivity){
        checkAttendActivity = new CheckAttend(this);
        int checkAttendPageIndex = ui->body->indexOf(ui->page_attend_check);
        ui->body->removeWidget(ui->page_attend_check);
        ui->body->insertWidget(checkAttendPageIndex, checkAttendActivity);
        ui->body->setCurrentIndex(checkAttendPageIndex);
    }
}



Widget::~Widget()
{
    delete ui;
    if(loginActivity){
        delete loginActivity;
    }
    if(checkAttendActivity){
        delete checkAttendActivity;
    }

}

