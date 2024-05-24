#ifndef DIALOGUSERDETAIL_H
#define DIALOGUSERDETAIL_H

#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include "ui_dialoguserdetail.h"
class DIalogUserDetail : public QDialog
{
public:
    explicit DIalogUserDetail(QWidget *parent = nullptr);
    ~DIalogUserDetail();

private:
    Ui::DialogUserDetail *ui;
 };

#endif // DIALOGUSERDETAIL_H
