#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>

class APIhandler : public QObject
{
    Q_OBJECT
public:
    explicit APIhandler();
    ~APIhandler();
    void getRequest(QString url);
    void postRequest(QString url, QJsonArray jsonMessage);

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
