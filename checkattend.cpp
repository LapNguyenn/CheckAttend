#include "checkattend.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QComboBox>
#include "delegatetable.h"

CheckAttend::CheckAttend(QWidget *parent)
    : QWidget(parent), ui(new Ui::CheckAttendWidget)
{
    ui->setupUi(this);
    loading = new LoadingAnimation(ui->l_loading, parent);
    getListStudent();
}

void CheckAttend::getListStudent()
{
    QString urlGetList = "http://26.244.155.247:9191/get_tables/Student";
    apiHandler = new APIhandler();
    apiHandler->getRequest(urlGetList);
    loading->startLoading();
    connect(apiHandler, &APIhandler::finishConnect, loading, &LoadingAnimation::stopLoading);
    connect(apiHandler, &APIhandler::connectSuccess, this, &CheckAttend::displayList);
    connect(apiHandler, &APIhandler::connectFailed, this, &CheckAttend::handleConnectFailed);
}

void CheckAttend::displayList(QByteArray list)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(list);
    if(!jsonResponse.isNull()){
        if(jsonResponse.isArray()){
            QJsonArray jsonArray = jsonResponse.array();
            for (const auto& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    QJsonObject jsonObject = jsonValue.toObject();
                    // int id = jsonObject["ID"].toInt();
                    // QString name = jsonObject["Name"].toString();
                    // QString date = jsonObject["Date"].toString();
                    // qDebug() << "ID:" << id << ", Name:" << name << ", Major:" << major;
                }
            }
        } else {
            qDebug() << "Json is not an array";
        }
    } else {
        qDebug() << "Wrong json format";
    }
    model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels({"ID", "Tên", "Ngày sinh", "Trạng thái"});
    for (int i = 0; i< 30; i++){
        QList<QStandardItem*>rowData;
        QStandardItem *itemId = new QStandardItem(QString::number(i));
        QStandardItem *itemName = new QStandardItem("Nguyen Thanh Lap");
        QStandardItem *itemDate = new QStandardItem("02/12/2003");

        itemId->setEditable(false);
        itemName->setEditable(false);
        itemDate->setEditable(false);

        rowData.append(itemId);
        rowData.append(itemName);
        rowData.append(itemDate);

        QString currentStatus = "Vắng";
        QStandardItem *attendStatus = new QStandardItem();
        attendStatus->setData(currentStatus, Qt::DisplayRole);
        attendStatus->setData(currentStatus, Qt::UserRole);

        rowData.append(attendStatus);
        model->appendRow(rowData);
    }
    ui->tb_student_list->setModel(model);
    ui->tb_student_list->setItemDelegateForColumn(3, new delegateTable());
    auto rowHeader = ui->tb_student_list->horizontalHeader();
    rowHeader->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->tb_student_list->model(), &QAbstractItemModel::dataChanged, this, &CheckAttend::handleUpdateAttendStatus);
}

void CheckAttend::handleUpdateAttendStatus(const QModelIndex &index)
{
    if(index.isValid()){
        int id = index.sibling(index.row(), 0).data(Qt::DisplayRole).toInt();
        qDebug() << "ID of change line: " << id;
    }
}

void CheckAttend::handleConnectFailed(QByteArray responseError)
{
    QIcon originalIcon(":/assets/icons/circle-red.svg");
    ui->bt_status_connect_api->setIcon(originalIcon);
    qDebug() << responseError;
}

CheckAttend::~CheckAttend()
{
    delete model;
    delete ui;
    delete apiHandler;
}
