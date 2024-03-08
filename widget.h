#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "login.h"

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
    void openLoginPage();
    void openMainPage();
    Ui::Widget *ui;
    Login *loginActivity;

private slots:
};
#endif // WIDGET_H
