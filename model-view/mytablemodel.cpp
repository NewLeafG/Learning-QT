#include "mytablemodel.h"
#include <QtMath>
#include <QColor>

MyTableModel::MyTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_columnNum=9;
}

void MyTableModel::setInitData(QList<CellInfo*>& data)
{
    //重置model数据之前调用beginResetModel，此时会触发modelAboutToBeReset信号
    beginResetModel();
    //重置model中的数据
    m_datas = data;
    m_rowNum = ceil(data.size()*1.0/m_columnNum);   //行数=数据总数/列数，然后向上取整
    //数据设置结束后调用endResetModel，此时会触发modelReset信号
    endResetModel();
}

int MyTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    } else {
        return m_rowNum;
    }
}

int MyTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    } else {
        return m_columnNum;
    }
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if(index.row()*m_columnNum+index.column() < m_datas.count())
    {
        if (role == Qt::DisplayRole ||  role == Qt::EditRole) {
            return m_datas[index.row()*m_columnNum+index.column()]->content;//数据的呈现形式
        }
        else if(role == Qt::DecorationRole){
            return m_datas[index.row()*m_columnNum+index.column()]->bgColor;//单元格背景色
        }
        else if (role == Qt::TextAlignmentRole) {    //对其方式
            return Qt::AlignCenter;
        }
        else if(role == Qt::ToolTipRole){
            return m_datas[index.row()*m_columnNum+index.column()]->toolTip;//数据的提示信息
        }
        else if(role == Qt::UserRole)
        {
            return QVariant::fromValue(m_datas[index.row()*m_columnNum+index.column()]);
        }
    }
    return QVariant();
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row()*m_columnNum+index.column() < m_datas.count())
    {
        if (index.isValid() && role == Qt::EditRole)
        {
            m_datas[index.row()*m_columnNum+index.column()]->content = value.value<QString>();
            emit dataChanged(index, index, QVector<int>() << role);                     //发送信号触发刷新
            return true;
        }
        if (index.isValid() && role == Qt::DecorationRole)
        {
            m_datas[index.row()*m_columnNum+index.column()]->bgColor = value.value<QColor>();
            emit dataChanged(index, index, QVector<int>() << role);                     //发送信号触发刷新
            return true;
        }
    }
    return false;
}
