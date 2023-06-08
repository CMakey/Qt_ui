
#include <QtWidgets>

#include "tableMdi.h"

TableMdiChild::TableMdiChild()
{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
}

//void TableMdiChild::newtable()
//{
//    static int sequenceNumber = 1;

//    isUntitled = true;
//    curFile = tr("document%1.txt").arg(sequenceNumber++);
//    setWindowTitle(curFile + "[*]");

//    connect(document(), &QTextDocument::contentsChanged,
//            this, &MdiChild::documentWasModified);
//}
void TableMdiChild::newtable()
{
    // 创建表格模型
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setRowCount(4);  // 设置行数
    model->setColumnCount(4);  // 设置列数

    // 设置列表头
    QStringList headerLabels;
    headerLabels << "a" << "b" << "c" << "d";
    model->setHorizontalHeaderLabels(headerLabels);

    // 设置行表头
    QStringList verticalHeaderLabels;
    verticalHeaderLabels << "1" << "2" << "3" << "4";
    model->setVerticalHeaderLabels(verticalHeaderLabels);

    // 设置单元格内容
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            QStandardItem *item = new QStandardItem("0");
            model->setItem(row, col, item);
        }
    }

    // 设置模型
    setModel(model);

    // 设置表格样式和调整列宽和行高等
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
