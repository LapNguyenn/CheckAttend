#include "MyMqttClient.h"

QMqttClient *MyMQttClient::client() const
{
    return m_client;
}
