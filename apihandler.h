#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class APIhandler : public QObject
{
    Q_OBJECT
public:
    APIhandler();
    ~APIhandler();
    void getRequest(QString url);
    void postRequest(QString url, QHttpMultiPart *message);

signals:
    void finishConnect();
    void connectSuccess(QByteArray result);
    void connectFailed(QByteArray result);
private slots:
    void handleConect();
private:
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;
};

#endif // APIHANDLER_H
