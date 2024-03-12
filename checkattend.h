#ifndef CHECKATTEND_H
#define CHECKATTEND_H

#include <QObject>
#include <QWidget>
#include "apihandler.h"
#include "QNetworkReply"
#include "QStandardItemModel"
#include "ui_checkattend.h"

class CheckAttend : public QWidget
{
    Q_OBJECT
public:
    CheckAttend(QWidget *parent = nullptr);
    ~CheckAttend();

private slots:
    void handleConnectSuccess();
    void handleConnectFailed();
    void handleUpdateAttendStatus(const QModelIndex &index);
private:
    void displayList();
    APIhandler *apiHandler;
public:
    Ui::CheckAttendWidget *ui;
    QStandardItemModel *model;
};

#endif // CHECKATTEND_H
