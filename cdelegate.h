#ifndef CDELEGATE_H
#define CDELEGATE_H

#include <QStyledItemDelegate>
#include "cuserdata.h"

class CDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    QWidget *createCellEditor(const CUserData *cell, QWidget *parent) const;
public:
    CDelegate(QWidget *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CDELEGATE_H
