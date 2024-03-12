#include "apihandler.h"

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

void APIhandler::postRequest(QString url, QHttpMultiPart *message)
{
    request->setUrl(QUrl(url));
    reply = manager->post(*request, message);
    connect(reply, &QNetworkReply::finished, this, &APIhandler::handleConect);
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
            errorMessage.append("\nError: Host not found");
            break;
        case QNetworkReply::ConnectionRefusedError:
            errorMessage.append("\nError: Connection refused");
            break;
        case QNetworkReply::TimeoutError:
            errorMessage.append("\nError: Timeout");
            break;
        default:
            errorMessage.append("\nError: Unknown error");
            break;
        }
        emit connectFailed(errorMessage);
    }
    reply->deleteLater();
}

