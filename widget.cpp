#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableListAttend->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableListAttend->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    mqttClient = new mqttclient(ui, this);
    connect(mqttClient, &mqttclient::connectSuccess,this, &Widget::handleMqttConnectSuccess);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handleMqttConnectSuccess()
{
    ui->label_broker_status_connect->setText("Connected!");
    ui->stackedWidget->setCurrentIndex(1);// to MainPage
    ui->stackedWidget_2->setCurrentIndex(1);
    checkattend = new CheckAttend(ui, this);
}
