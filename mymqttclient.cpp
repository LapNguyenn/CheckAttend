#include "mymqttclient.h"
#include <QTimer>

MyMQttClient &MyMQttClient::getInstance(QWidget *parent) {
    static MyMQttClient instance;
    return instance;
}

MyMQttClient::MyMQttClient(QWidget *parent)
    : QObject(nullptr), m_client(new QMqttClient)
{
    m_client->setHostname("192.168.137.212");
    m_client->setPort(static_cast<quint16>(21213));
    m_client->setUsername("admin");
    m_client->setPassword("admin");
    m_client->connectToHost();
    //Connect to mqtt broker
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [this, timer](){
        if(m_client->state() == QMqttClient::Connected){
            timer->stop();
            qDebug() << "Connect to mqtt server successfully!";
            emit connectSuccess();
            timer->deleteLater();
        }
    });
    timer->start(1000);
    timer->singleShot(5000, this, [this, timer](){
        if(m_client->state() != QMqttClient::Connected){
            emit connectFailed();
            emit disconnected();
            qDebug() << "Error. " << "Timeout: Connection Timeout.";
            timer->deleteLater();
        }
    });
    //Handle When connect success to server
    connect(this, &MyMQttClient::connectSuccess, this, [=](){
        auto subscription = m_client->subscribe(QString("mqtt/face/1792832/Access"));
        if(!subscription){
            qDebug() << "Subcribe mqtt/face/1792832/Access failed!";
        }else {
            qDebug() << "Subcribe mqtt/face/1792832/Access success!";
        }
    });
    //handle when received new message from topic
    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        QString topicString = QString::fromStdString(topic.name().toStdString());
        emit newMessage(QString(message), topicString);
    });
    //handle when disconnected to server
    connect(m_client, &QMqttClient::disconnected, this, [=](){
        emit disconnected();
    });
}

MyMQttClient::~MyMQttClient()
{
    delete m_client;
}
