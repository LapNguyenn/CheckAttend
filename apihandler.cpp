#include "apihandler.h"
#include <QJsonDocument>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QByteArray>

APIhandler::APIhandler()
{
    manager = new QNetworkAccessManager(this);
    request = new QNetworkRequest();
}

APIhandler::~APIhandler()
{
    delete manager;
    delete request;
    if (reply) {
        delete reply;
    }
}

void APIhandler::getRequest(QString url)
{
    request->setUrl(QUrl(url));
    reply = manager->get(*request);
    qDebug() << "Starting get method for " << url;
    connect(reply, &QNetworkReply::finished, this, &APIhandler::handleConect);
}

void APIhandler::postRequest(QString url, QJsonArray jsonMessage)
{
    request->setUrl(QUrl(url));
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument jsonDoc(jsonMessage);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    reply = manager->post(*request, jsonString.toUtf8());
    qDebug() << "Starting post method for " << url;
    connect(reply, &QNetworkReply::finished, this, &APIhandler::handleConect);
    connect(reply, &QNetworkReply::errorOccurred, [this](QNetworkReply::NetworkError error) {
        qDebug() << "Network error:" << error;
    });
}

void APIhandler::handleConect()
{
    emit finishConnect();
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        emit connectSuccess(responseData);
    } else {
        QByteArray errorMessage = reply->errorString().toUtf8();
        switch (reply->error()) {
        case QNetworkReply::HostNotFoundError:
            errorMessage.append("Error: Host not found");
            break;
        case QNetworkReply::ConnectionRefusedError:
            errorMessage.append("Error: Connection refused");
            break;
        case QNetworkReply::TimeoutError:
            errorMessage.append("Error: Timeout");
            break;
        default:
            errorMessage.append("Error: Unknown error");
            break;
        }
        emit connectFailed(errorMessage);
    }
    reply->deleteLater();
}

