#ifndef CHECKATTEND_H
#define CHECKATTEND_H

#include <QObject>
#include <QWidget>
#include "apihandler.h"
#include "QNetworkReply"
#include "QStandardItemModel"
#include "ui_checkattend.h"
#include "loadinganimation.h"

class CheckAttend : public QWidget
{
    Q_OBJECT
public:
    CheckAttend(QWidget *parent = nullptr);
    ~CheckAttend();

private slots:
    void handleConnectFailed(QByteArray responseError);
    void handleUpdateAttendStatus(const QModelIndex &index);
private:
    void getListStudent();
    void displayList(QByteArray list);
    APIhandler *apiHandler;
public:
    Ui::CheckAttendWidget *ui;
    QStandardItemModel *model;
    LoadingAnimation *loading;
};

#endif // CHECKATTEND_H
