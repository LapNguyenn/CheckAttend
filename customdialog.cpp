#include "customdialog.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QTextEdit>
#include "ui_userinfor"

CustomDialog::CustomDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Chi tiết");
    QLabel *label = new QLabel("Thông tin chi tiết người dùng", this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(label);

    // Tạo label cho hình ảnh và hiển thị ảnh
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setFixedSize(256, 304);
    imageLabel->setAlignment(Qt::AlignCenter);
    QPixmap pixmap(":/assets/img/bmp/Lap.bmp");
    pixmap.scaled(QSize(256, 304));
    imageLabel->setPixmap(pixmap);


    // Tạo label cho thông tin người dùng và hiển thị nội dung
    QTextEdit *userInfoTextEdit = new QTextEdit(this);
    userInfoTextEdit->setPlainText("userInfo");
    userInfoTextEdit->setReadOnly(true);

    // Sắp xếp layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addWidget(imageLabel);
    contentLayout->addWidget(userInfoTextEdit);
    mainLayout->addLayout(contentLayout);
    setLayout(mainLayout);

    setLayout(layout);
}

CustomDialog::~CustomDialog()
{

}
