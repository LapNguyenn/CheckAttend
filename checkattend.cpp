#include "checkattend.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QComboBox>
#include <QMessageBox>
#include <QPixmap>
#include <QByteArray>
#include "delegatetable.h"
#include "TokenManager.h"
#include "MyDateTime.h"

CheckAttend::CheckAttend(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::CheckAttendWidget),
    apiHost("http://192.168.137.245:6969")
{
    ui->setupUi(this);
    ui->bt_submit->setEnabled(false);

    loading = new LoadingAnimation(ui->lbl_loading, parent);
    qDebug() << MyDateTime::getInstance().getTime();
    initMqtt();
    verifyTokenAPI();
    // displayListTest();
}

void CheckAttend::verifyTokenAPI()
{
    QString apiRequest = apiHost + "/connect/" + TokenManager::getInstance().getToken();
    if(apiHandler){
        disconnect(apiHandler);
    }
    apiHandler = new APIhandler();
    apiHandler->getRequest(apiRequest);
    loading->startLoading();
    ui->lbl_loading_info->setText("Đang kết nối tới máy chủ...");
    connect(apiHandler, &APIhandler::finishConnect, this, [&](){
        ui->lbl_loading_info->setText("");
        loading->stopLoading();
    });
    connect(apiHandler, &APIhandler::connectSuccess, this, [this](QByteArray userInfo){
        getListStudent();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(userInfo);
        if(jsonResponse.isObject()){
            QJsonObject jsonObj = jsonResponse.object();
            ui->l_teacher_name->setText("Teacher name: " + jsonObj["Name"].toString());
        }
    });
}

void CheckAttend::getListStudent()
{
    if(apiHandler){
        disconnect(apiHandler);
    }
    apiHandler = new APIhandler();
    // QString apiRequest = apiHost + "/attendance/getlist/" + TokenManager::getInstance().getToken() + "/" + MyDateTime::getInstance().getTime();
    QString apiRequest = apiHost + "/attendance/getlist/"+ TokenManager::getInstance().getToken() + "/2024-03-21+08:45:00";
    apiHandler->getRequest(apiRequest);
    loading->startLoading();
    ui->lbl_loading_info->setText("Đang lấy danh sách sinh viên...");
    connect(apiHandler, &APIhandler::finishConnect, this, [&](){
        ui->lbl_loading_info->setText("");
        loading->stopLoading();
    });
    connect(apiHandler, &APIhandler::connectSuccess, this, &CheckAttend::displayList);
    connect(apiHandler, &APIhandler::connectFailed, this, &CheckAttend::handleConnectFailed);
}

void CheckAttend::displayList(QByteArray list)
{
    ui->bt_submit->setEnabled(true);
    QIcon icon(":/assets/icons/circle-green.svg");
    ui->bt_status_connect_api->setIcon(icon);
    model = new QStandardItemModel(this);
    model->setColumnCount(5);
    // model->setHorizontalHeaderLabels({"ID", "Tên", "Ngày sinh", "Trạng thái", "Thời gian", "Khuôn mặt"});
    model->setHorizontalHeaderLabels({"ID", "Tên", "Ngày sinh", "Trạng thái", "Thời gian"});
    QJsonDocument jsonResponse = QJsonDocument::fromJson(list);
    if(!jsonResponse.isNull()){
        QJsonArray jsonArray = jsonResponse.array();
        ui->l_class->setText("Class : " + jsonArray.at(0).toObject()["Class_name"].toString());
        for (const auto& jsonValue : jsonArray) {
            if (jsonValue.isObject()) {
                QList<QStandardItem*>rowData;
                QJsonObject jsonObject = jsonValue.toObject();
                QStandardItem *itemId = new QStandardItem(jsonObject["ID"].toString());
                QStandardItem *itemName = new QStandardItem(jsonObject["Name"].toString());
                QStandardItem *itemDate = new QStandardItem(jsonObject["Date"].toString());
                itemId->setEditable(false);
                itemName->setEditable(false);
                itemDate->setEditable(false);
                QString currentStatus = "Vắng";
                if(jsonObject["Status"].toBool()){
                    currentStatus = "Có mặt";
                }
                QStandardItem *attendStatus = new QStandardItem();
                attendStatus->setData(currentStatus, Qt::DisplayRole);
                attendStatus->setData(currentStatus, Qt::UserRole);
                QStandardItem *itemAttendTime = new QStandardItem(MyDateTime::getInstance().getTime());
                itemAttendTime->setEditable(false);

                // QLabel *imageLabel = new QLabel;
                // imageLabel->setFixedSize(128, 152);
                // imageLabel->setAlignment(Qt::AlignCenter);
                // QPixmap pixmap(":/assets/img/defaultPic.jpg");
                // imageLabel->setPixmap(pixmap);
                // QStandardItem *itemFaceImage = new QStandardItem();
                // itemFaceImage->setData(QVariant::fromValue(pixmap), Qt::DecorationRole);
                // itemFaceImage->setEditable(false);

                rowData.append(itemId);
                rowData.append(itemName);
                rowData.append(itemDate);
                rowData.append(attendStatus);
                rowData.append(itemAttendTime);
                // rowData.append(itemFaceImage);
                model->appendRow(rowData);
            }
        }
    }
    ui->tb_student_list->setModel(model);
    ui->tb_student_list->setItemDelegateForColumn(3, new delegateTable());
    auto rowHeader = ui->tb_student_list->horizontalHeader();
    ui->tb_student_list->resizeRowsToContents();
    rowHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    rowHeader->setSectionResizeMode(1, QHeaderView::Stretch);
    rowHeader->setSectionResizeMode(2, QHeaderView::Stretch);
    rowHeader->setSectionResizeMode(3, QHeaderView::Stretch);
    rowHeader->setSectionResizeMode(4, QHeaderView::Stretch);
    // rowHeader->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    connect(ui->le_search, &QLineEdit::textChanged, this, &CheckAttend::searchById);
    connect(ui->bt_submit, &QPushButton::clicked, this, &CheckAttend::submitToJson);
    connect(ui->tb_student_list->model(), &QAbstractItemModel::dataChanged, this, [&](const QModelIndex &index){
        if(index.isValid()){
            model->setData(index.sibling(index.row(), 4), MyDateTime::getInstance().getTime(), Qt::EditRole);
        }
    });
}

// void CheckAttend::displayListTest()
// {
//     ui->bt_submit->setEnabled(true);
//     model = new QStandardItemModel(this);
//     model->setColumnCount(5);
//     model->setHorizontalHeaderLabels({"ID", "Tên", "Ngày sinh", "Trạng thái", "Thời gian", "Khuôn mặt"});

//     QStringList idList, nameList, dateList;
//     idList << "201203" <<"201342" <<"205344" <<"212212"<<"201213";
//     nameList << "Nguyễn Văn Núi" << "Nguyễn Thanh Thản" <<"Vũ Công Kềnh" << "Nguyễn Thành Lập" << "Lê Văn Vở";
//     dateList << "01-05-2003" <<"01-07-2003" << "12-02-2003" <<"02-12-2003" <<"28-02-2003";
//     for(int i = 0; i< 5; i++){
//         QList<QStandardItem*>rowData;
//         QStandardItem *itemId = new QStandardItem(idList[i]);
//         QStandardItem *itemName = new QStandardItem(nameList[i]);
//         QStandardItem *itemDate = new QStandardItem(dateList[i]);
//         itemId->setEditable(false);
//         itemName->setEditable(false);
//         itemDate->setEditable(false);
//         QString currentStatus = "Vắng";
//         QStandardItem *attendStatus = new QStandardItem();
//         attendStatus->setData(currentStatus, Qt::DisplayRole);
//         QStandardItem *itemAttendTime = new QStandardItem("");
//         itemAttendTime->setEditable(false);
//         QStandardItem *itemFaceImage = new QStandardItem("");
//         itemFaceImage->setEditable(false);
//         rowData.append(itemId);
//         rowData.append(itemName);
//         rowData.append(itemDate);
//         rowData.append(attendStatus);
//         rowData.append(itemAttendTime);
//         rowData.append(itemFaceImage);
//         model->appendRow(rowData);
//     }
//     ui->tb_student_list->setModel(model);
//     ui->tb_student_list->setItemDelegateForColumn(3, new delegateTable());
//     ui->tb_student_list->setItemDelegateForColumn(5, new delegateTable());
//     auto rowHeader = ui->tb_student_list->horizontalHeader();
//     ui->tb_student_list->resizeRowsToContents();
//     rowHeader->setSectionResizeMode(0, QHeaderView::Stretch);
//     rowHeader->setSectionResizeMode(1, QHeaderView::Stretch);
//     rowHeader->setSectionResizeMode(2, QHeaderView::Stretch);
//     rowHeader->setSectionResizeMode(3, QHeaderView::Stretch);
//     rowHeader->setSectionResizeMode(4, QHeaderView::Stretch);
//     rowHeader->setSectionResizeMode(5, QHeaderView::Stretch);
//     connect(ui->le_search, &QLineEdit::textChanged, this, &CheckAttend::searchById);
//     connect(ui->bt_submit, &QPushButton::clicked, this, &CheckAttend::submitToJson);
//     connect(ui->tb_student_list->model(), &QAbstractItemModel::dataChanged, this, [&](const QModelIndex &index){
//         if(index.isValid()){
//             model->setData(index.sibling(index.row(), 4), MyDateTime::getInstance().getTime(), Qt::UserRole);
//         }
//     });
// }

void CheckAttend::searchById(const QString &inputId)
{
    if(!model) return;
    for (int row = 0; row < model->rowCount(); row++) {
        QModelIndex index = model->index(row, 0);
        QString studentId = model->data(index, Qt::DisplayRole).toString();
        if(studentId.contains(inputId, Qt::CaseInsensitive)) {
            ui->tb_student_list->showRow(row);
        } else {
            ui->tb_student_list->hideRow(row);
        }
    }
}

void CheckAttend::submitToJson()
{
    if(!model) return;
    QMessageBox verifyAction(QMessageBox::Question,
                             tr("Xác nhận lưu"),
                             tr("Lưu và gửi danh sách lên máy chủ?"),
                             QMessageBox::Yes | QMessageBox::No,
                             this);;
    verifyAction.setDefaultButton(QMessageBox::No);
    if (verifyAction.exec() == QMessageBox::Yes){
        if(apiHandler){
            disconnect(apiHandler);
        }
        apiHandler = new APIhandler();
        QString apiRequest = apiHost + "/attendance/mark/";
        QJsonArray jsonArray;
        for (int row = 0; row < model->rowCount(); row++) {
            QJsonObject jsonObject;
            QVariant id, statusAttend, dateTime;
            id = model->index(row, 0).data(Qt::DisplayRole);
            if(model->index(row, 3).data(Qt::DisplayRole).toString().compare("Vắng") == 0){
                statusAttend = "0";
            } else {
                statusAttend = "1";
            }
            dateTime = model->index(row, 4).data(Qt::DisplayRole);
            jsonObject.insert("ID", QJsonValue::fromVariant(id));
            jsonObject.insert("Status", QJsonValue::fromVariant(statusAttend));
            jsonObject.insert("DateTime", QJsonValue::fromVariant(dateTime));
            jsonArray.append(jsonObject);
        }
        qDebug() << jsonArray;
        //Send to server
        apiHandler->postRequest(apiRequest, jsonArray);
        ui->tb_student_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->bt_submit->setEnabled(false);
        loading->startLoading();
        ui->lbl_loading_info->setText("Đang gửi...");
        connect(apiHandler, &APIhandler::finishConnect, this, [this](){
            ui->tb_student_list->setEditTriggers(QAbstractItemView::AllEditTriggers);
            ui->bt_submit->setEnabled(true);
            loading->stopLoading();
            ui->lbl_loading_info->setText("");
        });
        connect(apiHandler, &APIhandler::connectSuccess, this, [this](QByteArray response){
            qDebug() << response;
            QMessageBox::information(nullptr, "Thành công", "Gửi thành công đến hệ thống!");
        });
        connect(apiHandler, &APIhandler::connectFailed, this, [this](){
            QMessageBox::information(nullptr, "Thất bại", "Đã xảy ra lỗi khi gửi đến hệ thống!");
        });
    }
}
void CheckAttend::initMqtt()
{

    connect(mqttclient::getInstance(), &mqttclient::connectSuccess, this, &CheckAttend::handleMqttConnectSuccess);
    connect(mqttclient::getInstance(), &mqttclient::disconnected, this, &CheckAttend::handleMqttDisconnected);
    connect(mqttclient::getInstance(), &mqttclient::newMessage, this, &CheckAttend::handleMqttMessage);
}
void CheckAttend::handleMqttMessage(QString message, QString topic) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    if(jsonObject.isEmpty()) return;
    if(!model) return;
    if(topic.compare("mqtt/face/1792832/Access") == 0) {
        for (int row = 0; row < model->rowCount(); row++) {
            QModelIndex index = model->index(row, 0);
            QString studentId = model->data(index, Qt::DisplayRole).toString();
            if(studentId.compare(jsonObject["ID"].toString()) == 0) {
                QModelIndex indexChange = model->index(row, 3);
                model->setData(indexChange, "Có mặt", Qt::DisplayRole);
            }
        }
    }
}



void CheckAttend::handleMqttConnectSuccess()
{
    QIcon icon(":/assets/icons/circle-green.svg");
    ui->bt_status_connect_mqtt->setToolTip("Đã kết nối với Camera AI");
    ui->bt_status_connect_mqtt->setIcon(icon);
}

void CheckAttend::handleMqttDisconnected()
{
    QIcon icon(":/assets/icons/circle-red.svg");
    ui->bt_status_connect_mqtt->setToolTip("Không thể kết nối với Camera AI");
    ui->bt_status_connect_mqtt->setIcon(icon);
}

void CheckAttend::handleConnectFailed(QByteArray responseError)
{
    QIcon icon(":/assets/icons/circle-red.svg");
    ui->bt_status_connect_api->setIcon(icon);
    qDebug() << responseError;
}

CheckAttend::~CheckAttend()
{
    delete model;
    delete ui;
    delete apiHandler;
    // delete m_client;
    delete loading;
}
