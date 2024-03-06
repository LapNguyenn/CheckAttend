#ifndef CHECKATTEND_H
#define CHECKATTEND_H

#include <QObject>
#include <QWidget>
#include "./ui_widget.h"
#include "apihandler.h"
#include "QNetworkReply"

class CheckAttend : public QWidget
{
    Q_OBJECT
public:
    CheckAttend(Ui::Widget *ui, QWidget *parent = nullptr);
    ~CheckAttend();

private slots:
    void handleConnectSuccess();
    void handleConnectFailed();
private:
    Ui::Widget *xUi;
    APIhandler *apiHandler;
};

#endif // CHECKATTEND_H
