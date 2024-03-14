#include "checkattend.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QComboBox>
#include "delegatetable.h"
#include <QTimeZone>
#include "TokenManager.h"

CheckAttend::CheckAttend(QWidget *parent)
    : QWidget(parent), ui(new Ui::CheckAttendWidget)
    , apiHost("http://26.244.155.247:9191")
{
    ui->setupUi(this);
    loading = new LoadingAnimation(ui->lbl_loading, parent);
    apiHandler = new APIhandler();
    initMqtt();
    // getListStudent();
    displayListTest();
}

void CheckAttend::verifyTokenAPI()
{
    QString apiRequest = apiHost + "/connect/" + TokenManager::getInstance().getToken();
    apiHandler->getRequest(apiRequest);
    loading->startLoading();
    connect(apiHandler, &APIhandler::finishConnect, loading, &LoadingAnimation::stopLoading);
    connect(apiHandler, &APIhandler::connectSuccess, this, [this](QByteArray userInfo){
        QJsonDocument jsonResponse = QJsonDocument::fromJson(userInfo);
        if(jsonResponse.isObject()){
            QJsonObject jsonObj = jsonResponse.object();
            ui->l_teacher_name->setText("Teacher name: " + jsonObj["Name"].toString());
        }
    });
}

void CheckAttend::getListStudent()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime.setTimeZone(QTimeZone("Asia/Ho_Chi_Minh"));
    QString apiRequest = apiHost + "/attendance/getlist/" + currentTime.toString("yyyy-MM-dd,hh:mm:ss");
    apiHandler->getRequest(apiRequest);
    loading->startLoading();
    connect(apiHandler, &APIhandler::finishConnect, loading, &LoadingAnimation::stopLoading);
    connect(apiHandler, &APIhandler::connectSuccess, this, &CheckAttend::displayList);
    connect(apiHandler, &APIhandler::connectFailed, this, &CheckAttend::handleConnectFailed);
}

void CheckAttend::displayList(QByteArray list)
{
    QIcon icon(":/assets/icons/circle-green.svg");
    ui->bt_status_connect_api->setIcon(icon);
    model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"ID", "Tên", "Ngày sinh", "Trạng thái"});
    QJsonDocument jsonResponse = QJsonDocument::fromJson(list);
    if(!jsonResponse.isNull()){
        if(jsonResponse.isArray()){
            QJsonArray jsonArray = jsonResponse.array();
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
                    if(jsonObject["AttendStatus"].toBool()){
                        currentStatus = "Có mặt";
                    }
                    QStandardItem *attendStatus = new QStandardItem();
                    attendStatus->setData(currentStatus, Qt::DisplayRole);
                    attendStatus->setData(currentStatus, Qt::UserRole);
                    rowData.append(itemId);
                    rowData.append(itemName);
                    rowData.append(itemDate);
                    rowData.append(attendStatus);
                    model->appendRow(rowData);
                    // qDebug() << "ID:" << id << ", Name:" << name << ", Major:" << major;
                }
            }
        } else {
            qDebug() << "Json is not an array";
        }
    } else {
        qDebug() << "Wrong json format";
    }
    ui->tb_student_list->setModel(model);
    ui->tb_student_list->setItemDelegateForColumn(3, new delegateTable());
    auto rowHeader = ui->tb_student_list->horizontalHeader();
    rowHeader->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->tb_student_list->model(), &QAbstractItemModel::dataChanged, this, &CheckAttend::handleUpdateAttendStatus);
    connect(ui->le_search, &QLineEdit::textChanged, this, &CheckAttend::searchById);
}



void CheckAttend::displayListTest()
{
    model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"ID", "Tên", "Ngày sinh", "Trạng thái"});
    ui->tb_student_list->setItemDelegateForColumn(3, new delegateTable());
    QStringList idList, nameList, dateList;
    idList << "201203" <<"201342" <<"205344" <<"212212"<<"201213";
    nameList << "Nguyễn Văn Núi" << "Nguyễn Thanh Thản" <<"Vũ Công kềnh" << "Nguyễn Thành Lập" << "Lê Văn Vở";
    dateList << "01-05-2003" <<"01-07-2003" << "12-02-2003" <<"02-12-2003" <<"28-02-2003";
    for(int i = 0; i< 5; i++){
        QList<QStandardItem*>rowData;
        QStandardItem *itemId = new QStandardItem(idList[i]);
        QStandardItem *itemName = new QStandardItem(nameList[i]);
        QStandardItem *itemDate = new QStandardItem(dateList[i]);
        itemId->setEditable(false);
        itemName->setEditable(false);
        itemDate->setEditable(false);
        QString currentStatus = "Vắng";
        QStandardItem *attendStatus = new QStandardItem();
        attendStatus->setData(currentStatus, Qt::DisplayRole);
        rowData.append(itemId);
        rowData.append(itemName);
        rowData.append(itemDate);
        rowData.append(attendStatus);
        model->appendRow(rowData);
    }
    ui->tb_student_list->setModel(model);
    auto rowHeader = ui->tb_student_list->horizontalHeader();
    rowHeader->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->tb_student_list->model(), &QAbstractItemModel::dataChanged, this, &CheckAttend::handleUpdateAttendStatus);
    connect(ui->le_search, &QLineEdit::textChanged, this, &CheckAttend::searchById);
}

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

void CheckAttend::handleUpdateAttendStatus(const QModelIndex &index)
{
    if(index.isValid()){
        int id = index.sibling(index.row(), 0).data(Qt::DisplayRole).toInt();
        qDebug() << "ID of change line: " << id;
    }
}

void CheckAttend::initMqtt()
{
    m_client = new mqttclient(this);
    connect(m_client, &mqttclient::connectSuccess, this, &CheckAttend::handleMqttConnectSuccess);
    connect(m_client, &mqttclient::disconnected, this, &CheckAttend::handleMqttDisconnected);
    connect(m_client, &mqttclient::newMessage, this, &CheckAttend::handleMqttMessage);
}

void CheckAttend::handleMqttMessage(QString message)
{
    //Expected message contain id,dateTime,1
    qDebug() << message;
    QStringList messList = message.split(",");
    if(!model) return;
    int row = 0;
    for (int row = 0; row < model->rowCount(); row++) {
        QModelIndex index = model->index(row, 0);
        QString studentId = model->data(index, Qt::DisplayRole).toString();
        if(studentId.compare(messList[0]) == 0) {
            QModelIndex indexChange = model->index(row, 3);
            model->setData(indexChange, "Có mặt", Qt::DisplayRole);
            break;
        }
    }
}

void CheckAttend::handleMqttConnectSuccess()
{
    QIcon icon(":/assets/icons/circle-green.svg");
    ui->bt_status_connect_mqtt->setIcon(icon);
}

void CheckAttend::handleMqttDisconnected()
{
    QIcon icon(":/assets/icons/circle-red.svg");
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
    delete m_client;
    delete loading;
}
