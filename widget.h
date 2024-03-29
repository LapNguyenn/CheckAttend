#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mqttclient.h"
#include "checkattend.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    mqttclient *mqttClient;
    CheckAttend *checkattend;

private slots:
    void handleMqttConnectSuccess();
};
#endif // WIDGET_H
