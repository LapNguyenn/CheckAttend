#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "login.h"
#include "checkattend.h"
#include "adminsystem.h"
#include "scheduleview.h"
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
    void openSchedulePage();
    void openAdminPage();
    void openLoginPage();
    void openMainPage();
    void openCheckAttendPage();
    void uncheckAllPageButton();
    Ui::Widget *ui;
    Login *loginActivity;
    CheckAttend *checkAttendActivity;
    AdminSystem *adminSystemActivity;
    ScheduleView *scheduleViewActivity;
private slots:
};
#endif // WIDGET_H
