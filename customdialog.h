#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H
#include <QDialog>

class CustomDialog : public QDialog
{
public:
    explicit CustomDialog(QWidget *parent = nullptr);
    ~CustomDialog();
};

#endif // CUSTOMDIALOG_H
