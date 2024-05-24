#include "scheduleview.h"
ScheduleView::ScheduleView(QWidget *parent)
    : QWidget(parent), ui(new Ui::ScheduleViewWidget)
{
    ui->setupUi(this);
}

ScheduleView::~ScheduleView()
{
    delete ui;
}
