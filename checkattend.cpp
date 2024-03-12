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
    QString urlGetList = "http://26.244.155.247:9191/get_tables/Student";
    apiHandler = new APIhandler(urlGetList);
    model = new QStandardItemModel(this);
    displayList();
}



void CheckAttend::handleConnectSuccess()
{
    QByteArray response = this->apiHandler->getResult();
    qDebug() << response;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    if(!jsonResponse.isNull()) {
        if(jsonResponse.isArray()) {
            QJsonArray jsonArray = jsonResponse.array();
            for (const auto& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    // QJsonObject jsonObject = jsonValue.toObject();
                    // int id = jsonObject["ID"].toInt();
                    // QString name = jsonObject["Name"].toString();
                    // QString major = jsonObject["Major"].toString();
                    // qDebug() << "ID:" << id << ", Name:" << name << ", Major:" << major;

                    // QList<QStandardItem*>rowData;
                    // rowData.append(new QStandardItem(QString::number(id)));
                    // rowData.append(new QStandardItem(name));
                    // rowData.append(new QStandardItem(major));

                    // QStandardItem *checkBoxItem = new QStandardItem();
                    // checkBoxItem->setData(id, Qt::UserRole);
                    // checkBoxItem->setCheckable(true);
                    // checkBoxItem->setCheckable(Qt::Unchecked);
                    // rowData.append(checkBoxItem);

                    // model->appendRow(rowData);
                }
            }
        } else {
            qDebug() << "JSON is not an array";
        }
    } else {
        qDebug() << "Wrong json format ";
    }
}

void CheckAttend::handleConnectFailed()
{

}

void CheckAttend::displayList()
{
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

CheckAttend::~CheckAttend()
{
    delete model;
    delete ui;
    delete apiHandler;
}
