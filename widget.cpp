#include "widget.h"
#include "./ui_widget.h"
#include "linux/reboot.h"
#include <QProcess>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    openLoginPage();
    bool ok;
    connect(ui->bt_shutdown, &QPushButton::clicked, this, [](){
        QProcess::execute("sudo poweroff");
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Tắt máy", "Bạn có muốn tắt máy không?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QProcess::startDetached("/sbin/shutdown -h now");
        }
    });
    connect(ui->bt_exit, &QPushButton::clicked, this, &QCoreApplication::quit);
}

void Widget::openLoginPage()
{
    if (!loginActivity) {
        loginActivity = new Login(this);
        ui->stackedWidget->insertWidget(0, loginActivity);
    }
    ui->stackedWidget->setCurrentIndex(0);
    connect(loginActivity, &Login::loginSuccess, this, [this](){
        openMainPage();
        ui->stackedWidget->removeWidget(loginActivity);
    });
}


void Widget::openMainPage()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->sideBar->setVisible(true);
    //Open check-attend page first
    if(!checkAttendActivity){
        checkAttendActivity = new CheckAttend(this);
        ui->body->insertWidget(0, checkAttendActivity);
    }
    if(!scheduleViewActivity){
        scheduleViewActivity = new ScheduleView(this);
        ui->body->insertWidget(1, scheduleViewActivity);
    }
    if(!adminSystemActivity){
        adminSystemActivity = new AdminSystem(this);
        ui->body->insertWidget(2, adminSystemActivity);
    }
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
        openSchedulePage();
    });
    connect(ui->bt_open_page_admin, &QPushButton::clicked, this, [&](){
        openAdminPage();
    });
}

void Widget::openCheckAttendPage()
{

    ui->stackedWidget->setCurrentIndex(0);
    ui->body->setCurrentIndex(0);
    ui->lbl_name_page->setText(ui->bt_open_attend_check->text());
    ui->bt_open_attend_check->setChecked(true);
    ui->bt_open_page_schedule->setChecked(false);
    ui->bt_open_page_admin->setChecked(false);
}
void Widget::openSchedulePage()
{

    ui->stackedWidget->setCurrentIndex(0);
    ui->body->setCurrentIndex(1);
    ui->bt_open_attend_check->setChecked(false);
    ui->bt_open_page_schedule->setChecked(true);
    ui->bt_open_page_admin->setChecked(false);
    ui->lbl_name_page->setText(ui->bt_open_page_schedule->text());
}

void Widget::openAdminPage()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->body->setCurrentIndex(2);
    ui->lbl_name_page->setText(ui->bt_open_page_admin->text());
    ui->bt_open_attend_check->setChecked(false);
    ui->bt_open_page_schedule->setChecked(false);
    ui->bt_open_page_admin->setChecked(true);
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
    if(scheduleViewActivity) {
        delete scheduleViewActivity;
    }
}





