#include "apihandler.h"

APIhandler::APIhandler(QString url)
{
    manager = new QNetworkAccessManager();
    request = new QNetworkRequest();
    request->setUrl(QUrl(url));
    reply = manager->get(*request);
    connect(reply, &QNetworkReply::finished, this, &APIhandler::handleConect);
    connect(this, &APIhandler::connectSuccess, this, &APIhandler::handleConnectSuccess);
    connect(this, &APIhandler::connectFailed, this, &APIhandler::handleConnectFailed);
}

APIhandler::~APIhandler()
{
    if(manager){
        delete manager;
    }
    if(request){
        delete request;
    }
    if(reply){
        delete reply;
    }
}

void APIhandler::handleConect()
{
    if(reply->error() == QNetworkReply::NoError) {
        emit connectSuccess();
    } else {
        emit connectFailed();
    }
}

void APIhandler::handleConnectSuccess()
{
    this->result = this->reply->readAll();
    qDebug() << "API data: " << this->result;
}

void APIhandler::handleConnectFailed()
{
    this->result = this->reply->errorString().toUtf8();
    qDebug() << "Error fetching data: " << this->reply->errorString();
}

QByteArray APIhandler::getResult()
{
    return result;
}


