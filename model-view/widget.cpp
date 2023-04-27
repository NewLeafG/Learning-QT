#include "widget.h"
#include "ui_widget.h"
#include "mytablemodel.h"
#include <QTableView>
#include <QListView>
#include <QVBoxLayout>
#include <QHeaderView>
#include "mycolorseldelegate.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QList<CellInfo*> multiplicationList;
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        {
            CellInfo* cell = new CellInfo;
            cell->content=QString("%1 * %2 = ?").arg(i).arg(j);//1*9乘法口诀表数据
            cell->toolTip=QString("%1*%2=%3").arg(i).arg(j).arg(i*j);//1*9乘法口诀表提示
            cell->bgColor=QColor(0,100,100);
            multiplicationList.append(cell);
        }
    }

    QVBoxLayout* layout = new QVBoxLayout;
    QTableView* view1 = new QTableView(this);
    view1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    MyTableModel* model1 = new MyTableModel(this);
    MyColorSelDelegate* editor = new MyColorSelDelegate(this);
    view1->setItemDelegate(editor);
    model1->setInitData(multiplicationList);//将数据传给model中
    view1->setModel(model1);//view和model的绑定
    layout->addWidget(view1);//添加到布局
    setLayout(layout);//当前widget使用布局
}

Widget::~Widget()
{
    delete ui;
}

