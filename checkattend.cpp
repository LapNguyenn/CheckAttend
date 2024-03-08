#include "checkattend.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QCheckBox>


CheckAttend::CheckAttend(Ui::Widget *ui, QWidget *parent)
 : QWidget(parent), xUi(ui)
{
    QString urlGetList = "http://26.244.155.247:9191/get_tables/Student";
    apiHandler = new APIhandler(urlGetList);
    model = new QStandardItemModel(this);

    connect(apiHandler, &APIhandler::connectSuccess, this, &CheckAttend::handleConnectSuccess);
}

CheckAttend::~CheckAttend()
{

}

void CheckAttend::handleConnectSuccess()
{
    QByteArray response = this->apiHandler->getResult();
    qDebug() << response;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    if(!jsonResponse.isNull()) {
        if(jsonResponse.isArray()) {
            model->setHorizontalHeaderLabels({"ID", "Name", "Major", "Attend Status"});
            QJsonArray jsonArray = jsonResponse.array();
            for (const auto& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    QJsonObject jsonObject = jsonValue.toObject();
                    int id = jsonObject["ID"].toInt();
                    QString name = jsonObject["Name"].toString();
                    QString major = jsonObject["Major"].toString();
                    qDebug() << "ID:" << id << ", Name:" << name << ", Major:" << major;

                    QList<QStandardItem*>rowData;
                    rowData.append(new QStandardItem(QString::number(id)));
                    rowData.append(new QStandardItem(name));
                    rowData.append(new QStandardItem(major));

                    QStandardItem *checkBoxItem = new QStandardItem();
                    checkBoxItem->setData(id, Qt::UserRole);
                    checkBoxItem->setCheckable(true);
                    checkBoxItem->setCheckable(Qt::Unchecked);
                    rowData.append(checkBoxItem);

                    model->appendRow(rowData);
                }
            }
            xUi->tableListAttend->setModel(model);

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

QStandardItemModel *CheckAttend::getModel() const
{
    return model;
}
