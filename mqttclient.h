#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QWidget>
#include <QMqttClient>

class mqttclient: public QObject
{
    Q_OBJECT
public:
    static mqttclient *getInstance(QWidget *parent = nullptr);

signals:
    void connectSuccess();
    void connectFailed();
    void disconnected();
    void newMessage(QString message, QString topic);
private:
    explicit mqttclient(QWidget *parent = nullptr);
    ~mqttclient();
    QMqttClient *m_client;
    static mqttclient *m_instance;
};

#endif // MQTTCLIENT_H
