#include "dialoguserdetail.h"

DIalogUserDetail::DIalogUserDetail(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::DialogUserDetail)
{
    ui->setupUi(this);
    setWindowTitle("Thông tin chi tiết");
    // ui->lbl_image->setFixedSize(128, 152);
    // ui->lbl_image->setAlignment(Qt::AlignCenter);
    // QPixmap pixmap(":/assets/img/bmp/Lap.bmp");
    // ui->lbl_image->setPixmap(pixmap);
}

DIalogUserDetail::~DIalogUserDetail()
{
    delete ui;
}
