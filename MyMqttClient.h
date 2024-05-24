#ifndef MYMQTTCLIENT_H
#define MYMQTTCLIENT_H
#include <QObject>
#include <QMqttClient>
#include <QTimer>
class MyMQttClient : public QObject
{
    Q_OBJECT
public:
    static MyMQttClient &getInstance(){
        static MyMQttClient instance;
        return instance;
    }
    void connectToHost(){
        if(m_client->state() == QMqttClient::Connected){
            return;
        }
        m_client->setHostname("192.168.137.212");
        m_client->setPort(static_cast<quint16>(21213));
        m_client->setUsername("admin");
        m_client->setPassword("admin");
        m_client->connectToHost();
    }
    bool isConnectedToHost(){
        return m_client->state() == QMqttClient::Connected;
    }

    QMqttClient* getClient() const{
        return m_client;
    }

signals:

private:
    explicit MyMQttClient();
    QMqttClient *m_client;
};

#endif // MYMQTTCLIENT_H
