#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class APIhandler : public QObject
{
    Q_OBJECT
public:
    APIhandler(QString url);
    ~APIhandler();

signals:
    void connectSuccess();
    void connectFailed();
private slots:
    void handleConect();
    void handleConnectSuccess();
    void handleConnectFailed();
private:
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
public:
    QByteArray result;
    QByteArray getResult() const;
};

#endif // APIHANDLER_H
