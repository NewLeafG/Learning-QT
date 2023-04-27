#include "mycolorseldelegate.h"
#include <QColorDialog>
#include <QApplication>
MyColorSelDelegate::MyColorSelDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

MyColorSelDelegate::~MyColorSelDelegate()
{

}

QWidget *MyColorSelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget* editor = new QColorDialog(parent);
    return editor;
}

void MyColorSelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void MyColorSelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QColorDialog* dlg = static_cast<QColorDialog*>(editor);
    model->setData(index, dlg->selectedColor(), Qt::DecorationRole);
}

void MyColorSelDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
