#include "mqttclient.h"
#include "QTimer"
#include "QMessageBox"
mqttclient::mqttclient(Ui::Widget *ui, QWidget *parent)
    : QWidget(parent), xUi(ui)
{
    m_client = new QMqttClient(this);
    m_client->setHostname("192.168.137.212");
    m_client->setPort(static_cast<quint16>(21213));
    m_client->setUsername("admin");
    m_client->setPassword("admin");
    m_client->connectToHost();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mqttclient::handleConnect);
    timer->start(1000);
    timer->singleShot(5000, this, [this](){
        if(m_client->state() != QMqttClient::Connected){
            QMessageBox::warning(nullptr, "Error", "Timeout: Connection Timeout.\n");
            xUi->label_broker_status_connect->setText("Failed to connect to mqtt broker!");
        }
    });
    connect(m_client, &QMqttClient::disconnected, this, &mqttclient::handleBrokerDisconnected);


}
void mqttclient::handleConnect()
{
    if(m_client->state() == QMqttClient::Connected){
        for(auto &timer : this->findChildren<QTimer*>()) {
            timer->stop();
            timer->deleteLater();
        }
        emit connectSuccess();
    }
}
void mqttclient::handleBrokerDisconnected()
{
    xUi->label_broker_status_connect->setText("Disconnected!");
}


mqttclient::~mqttclient()
{

}

