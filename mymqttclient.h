#ifndef MYMQTTCLIENT_H
#define MYMQTTCLIENT_H
#include <QObject>
#include <QMqttClient>
class MyMQttClient : public QObject
{
    Q_OBJECT
public:
    static MyMQttClient &getInstance(){
        static MyMQttClient instance;
        return instance;
    };

signals:

private:
    explicit MyMQttClient(QWidget *parent = nullptr);
    ~MyMQttClient();
    QMqttClient *m_client;
};

#endif // MYMQTTCLIENT_H
