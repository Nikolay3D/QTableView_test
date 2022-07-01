#include "cdelegate.h"
#include "types.h"
#include <QDebug>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>

QWidget *CDelegate::createCellEditor(const CUserData *cell, QWidget *parent) const
{
    if(TCell::TCELL_NONE == cell->user_type())
    {
        /// пустая ячейка без данных
        qDebug() << Q_FUNC_INFO << "TCELL_NONE, algorithm error!";  //сюда не должны попадать, т.к. у пустых ячеек нет флага редактирования
    }
    else if(TCell::TCELL_DOUBLE == cell->user_type())
    {
        QDoubleSpinBox *doubleSpinbox = new QDoubleSpinBox(parent);
        doubleSpinbox->setDecimals(6);// WARNING при открытии этого делегата точность числа будет уменьшена

        doubleSpinbox->setValue(cell->toDouble());

        return doubleSpinbox;
    }
    else if(TCell::TCELL_BOOL == cell->user_type())
    {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItem("TRUE", true);
        comboBox->addItem("FALSE", false);
        comboBox->setCurrentIndex(cell->toBool() ? 0 : 1);
        return comboBox;
    }
    else if(TCell::TCELL_STR == cell->user_type())
    {
        QLineEdit *lineedit = new QLineEdit(parent);
        lineedit->setText(cell->toString());
        lineedit->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        return lineedit;
    }

    return nullptr;
}

QWidget *CDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    if(index.isValid())
    {
        CUserData cell_data = qvariant_cast<CUserData>(index.data(Qt::EditRole));

        QWidget *w = createCellEditor(&cell_data, parent);
        return w;
    }

    return nullptr;

}

void CDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void CDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CUserData cell_data = qvariant_cast<CUserData>(index.data(Qt::EditRole));
    if(TCell::TCELL_DOUBLE == cell_data.user_type()){
        QDoubleSpinBox *doubleSpinbox = qobject_cast<QDoubleSpinBox*>(editor);
        cell_data.setValue(doubleSpinbox->value());
        cell_data.setIs_empty(false);
        model->setData(index, QVariant::fromValue(cell_data));
    }
    else if(TCell::TCELL_BOOL == cell_data.user_type()){
        QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
        cell_data.setValue(comboBox->currentData().toBool());
        cell_data.setIs_empty(false);
        model->setData(index, QVariant::fromValue(cell_data));
    }
    else if(TCell::TCELL_STR == cell_data.user_type()){
        QLineEdit *lineedit = qobject_cast<QLineEdit*>(editor);
        cell_data.setValue(lineedit->text());
        cell_data.setIs_empty(false);
        model->setData(index, QVariant::fromValue(cell_data));
    }

}

void CDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
