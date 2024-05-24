#ifndef ADMINSYSTEM_H
#define ADMINSYSTEM_H

#include <QObject>
#include <QWidget>
#include <QStandardItemModel>
#include "ui_adminsystem.h"
class AdminSystem : public QWidget
{
    Q_OBJECT
public:
    explicit AdminSystem(QWidget *parent = nullptr);
    ~AdminSystem();
private slots:
private:
    void handleMqttMessage(QString message, QString topic);
    void displayListDevice();
    void displayListUser();
    Ui::AdminSystemWidget *ui;
    QStandardItemModel *model;
};

#endif // ADMINSYSTEM_H
