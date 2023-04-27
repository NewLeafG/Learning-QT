#ifndef MYCOLORSELDELEGATE_H
#define MYCOLORSELDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class MyColorSelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MyColorSelDelegate(QObject *parent = nullptr);
    ~MyColorSelDelegate();

    //创建用于编辑模型数据的widget组件，如一个QSpinBox组件，或一个QComboBox组件；
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //从数据模型获取数据，供widget组件进行编辑；
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    //将widget上的数据更新到数据模型；
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    //用于给widget组件设置一个合适的大小；
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
signals:

};

#endif // MYCOLORSELDELEGATE_H
