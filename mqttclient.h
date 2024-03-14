#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QWidget>
#include <QMqttClient>

class mqttclient: public QObject
{
    Q_OBJECT
public:
    mqttclient(QWidget *parent = nullptr);
    ~mqttclient();

signals:
    void connectSuccess();
    void connectFailed();
    void disconnected();
    void newMessage(QString message);
private:
    QMqttClient *m_client;
};

#endif // MQTTCLIENT_H
