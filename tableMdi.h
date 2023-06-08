
#ifndef TABLEMDI_H
#define TABLEMDI_H

#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>


class TableMdiChild : public QTableView
{
    Q_OBJECT
public:
//    explicit TableMdiChild(QWidget *parent = nullptr) : QTableView(parent)
//    explicit TableMdiChild(QWidget *parent = nullptr)

//    {
//        // 创建表格模型
//        QStandardItemModel *model = new QStandardItemModel(this);
//        model->setRowCount(4);  // 设置行数
//        model->setColumnCount(4);  // 设置列数

//        // 设置列表头
//        QStringList headerLabels;
//        headerLabels << "a" << "b" << "c" << "d";
//        model->setHorizontalHeaderLabels(headerLabels);

//        // 设置行表头
//        QStringList verticalHeaderLabels;
//        verticalHeaderLabels << "1" << "2" << "3" << "4";
//        model->setVerticalHeaderLabels(verticalHeaderLabels);

//        // 设置单元格内容
//        for (int row = 0; row < 4; ++row) {
//            for (int col = 0; col < 4; ++col) {
//                QStandardItem *item = new QStandardItem("0");
//                model->setItem(row, col, item);
//            }
//        }

//        // 设置模型
//        setModel(model);

//        // 设置表格样式和调整列宽和行高等
//        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//        verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    }
    TableMdiChild();
    void newtable();

protected:
//    void closeEvent(QCloseEvent *event) override;

private slots:
//    void documentWasModified();

private:
//    bool maybeSave();
//    void setCurrentFile(const QString &fileName);
//    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;

};


#endif // TABLEMDI_H
