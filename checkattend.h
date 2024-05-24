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
#include "mymqttclient.h"

class CheckAttend : public QWidget
{
    Q_OBJECT
public:
    explicit CheckAttend(QWidget *parent = nullptr);
    ~CheckAttend();

private slots:
    void handleConnectFailed(QByteArray responseError);
    void handleMqttMessage(QString message, QString topic);
    void handleMqttConnectSuccess();
    void handleMqttDisconnected();
    void displayList(QByteArray list);
    void searchById(const QString &inputId);
    void submitToJson();
private:
    void initMqtt();
    void getListStudent();
    void verifyTokenAPI();
    APIhandler *apiHandler;
    Ui::CheckAttendWidget *ui;
    QStandardItemModel *model;
    LoadingAnimation *loading;

private:
    // mqttclient *m_client;
    QString apiHost;
    QStringList UserInfo;
private://for test
    void displayListTest();
};

#endif // CHECKATTEND_H
