#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QWidget>
#include <QMqttClient>

class mqttclient : public QWidget
{
    Q_OBJECT
public:
    mqttclient(QWidget *parent = nullptr);
    ~mqttclient();

signals:
    void connectSuccess();
    void connectFailed();
private slots:
    void handleConnect();
    void handleBrokerDisconnected();
private:
    Ui::Widget *xUi;
    QMqttClient *m_client;
};

#endif // MQTTCLIENT_H
