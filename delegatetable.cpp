#include "delegatetable.h"



delegateTable::delegateTable()
{

}

QWidget *delegateTable::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 3){
        QComboBox *editor = new QComboBox(parent);
        editor->addItem("Vắng");
        editor->addItem("Có mặt");
        editor->setStyleSheet("QComboBox {"
                              "padding: 1px;"
                              "border-radius: 5px;"
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
