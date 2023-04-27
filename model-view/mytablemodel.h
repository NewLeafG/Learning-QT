#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QColor>

struct CellInfo
{
    QString content;        //显示的内容
    QString toolTip;        //tooltips
    QColor bgColor;         //背景色
};

Q_DECLARE_METATYPE(CellInfo*)   //注册元数据类型

class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyTableModel(QObject *parent = nullptr);
    void setInitData(QList<CellInfo*>& data);
public:
    //返回行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    //返回列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //根据模型索引返回当前的数据
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    //设置value数据给index处的role角色
    bool setData(const QModelIndex& index, const QVariant &value, int role=Qt::EditRole) override;

private:
    int m_columnNum;                        //列大小
    int m_rowNum;                           //行大小
    QList<CellInfo*> m_datas;                    //数据
};

#endif // MYTABLEMODEL_H
