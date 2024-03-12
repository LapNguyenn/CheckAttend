#ifndef DELEGATETABLE_H
#define DELEGATETABLE_H
#include <QComboBox>
#include <QStyledItemDelegate>

class delegateTable : public QStyledItemDelegate
{
public:
    delegateTable();

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // DELEGATETABLE_H
