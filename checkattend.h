#ifndef CHECKATTEND_H
#define CHECKATTEND_H

#include <QObject>
#include <QWidget>
#include "apihandler.h"
#include "QNetworkReply"
#include "QStandardItemModel"
#include "ui_checkattend.h"
#include "loadinganimation.h"
#include "mqttclient.h"

class CheckAttend : public QWidget
{
    Q_OBJECT
public:
    explicit CheckAttend(QWidget *parent = nullptr);
    ~CheckAttend();

private slots:
    void handleConnectFailed(QByteArray responseError);
    void handleUpdateAttendStatus(const QModelIndex &index);
    void handleMqttMessage(QString message);
    void handleMqttConnectSuccess();
    void handleMqttDisconnected();
    void displayList(QByteArray list);
    void searchById(const QString &inputId);
private:
    void initMqtt();
    void getListStudent();
    void verifyTokenAPI();
    APIhandler *apiHandler;
    Ui::CheckAttendWidget *ui;
    QStandardItemModel *model;
    LoadingAnimation *loading;
    mqttclient *m_client;
private:
    QString apiHost;
    QStringList UserInfo;
private://for test
    void displayListTest();
};

#endif // CHECKATTEND_H
