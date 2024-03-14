#include "delegatetable.h"
#include <QPainter>


delegateTable::delegateTable()
{

}
void delegateTable::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool isSelected = option.state & QStyle::State_Selected;
    if(index.column() == 3) {
        QString attendStatus = index.data(Qt::DisplayRole).toString();
        QRect rect = option.rect;

        // // Default background color
        // painter->fillRect(rect, QColor(189,224,254));

        // Change background color
        if (attendStatus.compare("Vắng") == 0) {
            painter->fillRect(rect, QColor(230,57,70));
        } else if (attendStatus.compare("Có mặt") == 0) {
            painter->fillRect(rect, QColor(48,187,108));
        }
        QFont font = painter->font();
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, index.data(Qt::DisplayRole).toString());
        if (isSelected) {
            QPen pen(Qt::black);
            pen.setWidth(1);
            pen.setStyle(Qt::SolidLine);
            painter->setPen(pen);
            painter->drawRect(rect.adjusted(0, 0, -1, -1));
        }
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
QWidget *delegateTable::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 3){
        QComboBox *editor = new QComboBox(parent);
        editor->addItem("Vắng");
        editor->addItem("Có mặt");
        editor->setStyleSheet("QComboBox {"
                              "padding: 1px;"
                              "border-radius: 1px;"
                              "background-color: #bde0fe;"
                              "selection-background-color: #bde0fe;"
                              "color: black;"
                              "}"

                              "QComboBox::drop-down {"
                              "subcontrol-origin: padding;"
                              "subcontrol-position: top right;"
                              "width: 20%;"
                              "}"
                              );
        return editor;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void delegateTable::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(QComboBox *comboBox = qobject_cast<QComboBox*>(editor)) {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        comboBox->setCurrentText(value);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void delegateTable::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(QComboBox *comboBox = qobject_cast<QComboBox*>(editor)) {
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}


