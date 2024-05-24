#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QObject>
#include <QWidget>
#include "ui_scheduleview.h"

class ScheduleView : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleView(QWidget *parent = nullptr);
    ~ScheduleView();
    Ui::ScheduleViewWidget *ui;
};

#endif // SCHEDULEVIEW_H
