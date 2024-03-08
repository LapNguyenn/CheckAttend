#ifndef CHECKATTEND_H
#define CHECKATTEND_H

#include <QObject>
#include <QWidget>
#include "apihandler.h"
#include "QNetworkReply"
#include "QStandardItemModel"

class CheckAttend : public QWidget
{
    Q_OBJECT
public:
    CheckAttend(QWidget *parent = nullptr);
    ~CheckAttend();

private slots:
    void handleConnectSuccess();
    void handleConnectFailed();
private:
    APIhandler *apiHandler;
public:
    QStandardItemModel *model;
    QStandardItemModel *getModel() const;
};

#endif // CHECKATTEND_H
