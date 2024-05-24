#include "adminsystem.h"
#include "mqttclient.h"
#include "dialoguserdetail.h"
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QVariant>
#include <QPixmap>

AdminSystem::AdminSystem(QWidget *parent)
    : QWidget(parent), ui(new Ui::AdminSystemWidget)
{
    ui->setupUi(this);
    ui->page_manage->setCurrentIndex(0);
    displayListDevice();
    connect(ui->bt_manage_device, &QPushButton::clicked, this, &AdminSystem::displayListDevice);
    connect(ui->bt_manage_user, &QPushButton::clicked, this, &AdminSystem::displayListUser);
}



AdminSystem::~AdminSystem()
{
    delete ui;
    delete model;
}



void AdminSystem::displayListDevice()
{
    //ui
    ui->page_manage->setCurrentIndex(0);
    ui->bt_manage_device->setChecked(true);
    ui->bt_manage_user->setChecked(false);
    ui->bt_add_user->setVisible(false);
    //function
    model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"ID", "Tên", "IP", "Trạng thái"});

    // Sample data
    QStringList idList, nameList, ipList, statusList;
    idList << "1792832" <<"2032105";
    nameList << "Cam1" << "Cam2";
    ipList << "192.168.137.2" <<"192.168.137.3";
    statusList << "Kết nối" << "Mất kết nối";
    for(int i = 0; i < 2; i++) {
        QList<QStandardItem*> rowData;
        QStandardItem *itemId = new QStandardItem(idList[i]);
        QStandardItem *itemName = new QStandardItem(nameList[i]);
        QStandardItem *itemDate = new QStandardItem(ipList[i]);
        QStandardItem *itemStatus = new QStandardItem(statusList[i]);
        itemId->setEditable(false);
        itemName->setEditable(false);
        itemDate->setEditable(false);
        itemStatus->setEditable(false);
        rowData.append(itemId);
        rowData.append(itemName);
        rowData.append(itemDate);
        rowData.append(itemStatus);
        model->appendRow(rowData);
    }

    ui->tb_device_list->setModel(model);
    auto rowHeader = ui->tb_device_list->horizontalHeader();
    rowHeader->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tb_device_list, &QTableView::doubleClicked, this, [=](const QModelIndex &index) {
        if (index.column() == 2) {
            QString ipAddress = index.data().toString();
            QDesktopServices::openUrl(QUrl("http://" + ipAddress));
        }
    });
    // connect(mqttclient::getInstance(), &mqttclient::newMessage, this, &AdminSystem::handleMqttMessage);
}

void AdminSystem::displayListUser()
{
    //ui
    ui->page_manage->setCurrentIndex(1);
    ui->bt_manage_user->setChecked(true);
    ui->bt_manage_device->setChecked(false);
    ui->bt_add_user->setVisible(true);

    //function
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Danh sách", "Tên", "Giới tính", "Ảnh", "Thời gian đăng kí", "ID", "", ""});

    // Sample data
    QStringList idList, nameList, dateTimeList, picUrlList;

    nameList << "Linh"
             << "Nguyen Thanh Lap"
             << "Trinh Dinh Hoan"
             << "Tran Dang An"
             << "Lam"
             << "Nguyen Thanh Tung"
             << "Ngo Duy Hai";
    dateTimeList << "2022-12-29/02:15:10"
                 << "2024-03-15/15:12:06"
                 << "2024-03-15/14:21:09"
                 << "2024-03-15/15:59:11"
                 << "2024-03-15/16:09:06"
                 << "2024-03-21/14:34:31"
                 <<"2024-03-15/14:34:50";
    idList << "CS1000" <<"CS1004" << "CS1101" << "CS1003" << "CS21032" <<"CS1001" << "CS1002";
    picUrlList << ":/assets/img/bmp/SepLinh.bmp"
               << ":/assets/img/bmp/Lap.bmp"
               << ":/assets/img/bmp/Hoan.bmp"
               << ":/assets/img/bmp/An.bmp"
               << ":/assets/img/bmp/Lam.bmp"
               <<":/assets/img/bmp/Tung.bmp"
               <<":/assets/img/bmp/Hai.bmp";
    for(int i = 0; i < 7; i++) {
        QList<QStandardItem*> rowData;
        QStandardItem *itemTypeList = new QStandardItem("WhiteList");
        QStandardItem *itemName = new QStandardItem(nameList[i]);
        QStandardItem *itemGender = new QStandardItem("Nam");

        QLabel *imageLabel = new QLabel;
        imageLabel->setFixedSize(128, 152);
        imageLabel->setAlignment(Qt::AlignCenter);
        QPixmap pixmap(picUrlList[i]);
        imageLabel->setPixmap(pixmap);
        QStandardItem *itemFaceImage = new QStandardItem();
        itemFaceImage->setData(QVariant::fromValue(pixmap), Qt::DecorationRole);

        QStandardItem *itemDateTime = new QStandardItem(dateTimeList[i]);
        QStandardItem *itemId = new QStandardItem(idList[i]);

        QIcon icon1(":/assets/icons/ic_edit.svg");
        QStandardItem *itemEditUser = new QStandardItem();
        itemEditUser->setIcon(icon1);

        QIcon icon2(":/assets/icons/ic_delete.svg");
        QStandardItem *itemDeleteUser = new QStandardItem();
        itemDeleteUser->setIcon(icon2);

        itemTypeList->setEditable(false);
        itemName->setEditable(false);
        itemGender->setEditable(false);
        itemFaceImage->setEditable(false);
        itemDateTime->setEditable(false);
        itemId->setEditable(false);
        itemEditUser->setEditable(false);
        itemDeleteUser->setEditable(false);

        rowData.append(itemTypeList);
        rowData.append(itemName);
        rowData.append(itemGender);
        rowData.append(itemFaceImage);
        rowData.append(itemDateTime);
        rowData.append(itemId);
        rowData.append(itemEditUser);
        rowData.append(itemDeleteUser);
        model->appendRow(rowData);
    }

    ui->tb_user_list->setModel(model);
    // auto colHeader = ui->tb_user_list->horizontalHeader();
    // colHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tb_user_list->resizeRowsToContents();

    connect(ui->tb_user_list, &QTableView::doubleClicked, this, [=](const QModelIndex &index) {
        DIalogUserDetail dialogUserDetail;
        dialogUserDetail.exec();
    });
}

void AdminSystem::handleMqttMessage(QString message, QString topic)
{
    // if(topic.compare(""))
}

