#include "mqttclient.h"
#include "QTimer"
#include "QMessageBox"
mqttclient *mqttclient::getInstance(QWidget *parent)
{
    if (!m_instance) {
        m_instance = new mqttclient(parent);
    }
    return m_instance;
}
mqttclient *mqttclient::m_instance = nullptr;

mqttclient::mqttclient(QWidget *parent)
    : m_client(new QMqttClient())
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
    connect(this, &mqttclient::connectSuccess, this, [=](){
        auto subscription1 = m_client->subscribe(QString("mqtt/face/1792832/Access"));
        auto subscription2 = m_client->subscribe(QString("mqtt/face/1792832/online"));
        auto subscription3 = m_client->subscribe(QString("mqtt/face/2032105/Access"));
        auto subscription4 = m_client->subscribe(QString("mqtt/face/2032105/online"));
        if(!subscription1 && !subscription2 && !subscription3 && subscription4){
            qDebug() << "Subcribe all topic failed!";
        }else {
            qDebug() << "Subcribe all topic success!";
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

mqttclient::~mqttclient()
{
    delete m_client;
}

