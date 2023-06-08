
#include "mdi_test.h"
#include "ui_mdi_test.h"
#include "curveMdi.h"
#include "tableMdi.h"
#include "videoMdi.h"

#include <QMdiArea>

mdi_test::mdi_test(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mdi_test)
{
    ui->setupUi(this);

    //显示默认窗口
    SmoothCurve *child1 = new SmoothCurve;
    ui->mdiArea->addSubWindow(child1);
    child1->show();

    TableMdiChild *child2 = new TableMdiChild;
    ui->mdiArea->addSubWindow(child2);
    child2->show();

}

mdi_test::~mdi_test()
{
    delete ui;
}



void mdi_test::on_actionnew_table_triggered()
{
    TableMdiChild *child = new TableMdiChild;
    ui->mdiArea->addSubWindow(child);

    child->newtable();
    child->show();
}


void mdi_test::on_actionnew_video_triggered()
{
//    VideoMdiChild *child = new VideoMdiChild;

//    ui->mdiArea->addSubWindow(child);

//    VideoMdiChild videoMdiChild;
//    imagePath = videoMdiChild.setImagePath("D:/lyc-project/resource/pics/OIP.jpg");
//    child->showImage(imagePath);
//    child->show();
    VideoMdiChild *child = new VideoMdiChild;
    ui->mdiArea->addSubWindow(child);

    QString imagePath = child->setImagePath();
    if (!imagePath.isEmpty())
    {
        child->showImage(imagePath);
        child->show();
    }

}


void mdi_test::on_actionnew_curve_triggered()
{
    SmoothCurve *child = new SmoothCurve;
    ui->mdiArea->addSubWindow(child);

//    SmoothCurve smoothCurve;
//    QVector<QPointF> data = smoothCurve.readDataFromCSV("D:/lyc-project/resource/csv/random.CSV");
    QVector<QPointF> data = child->readDataFromCSV("D:/lyc-project/resource/csv/random.CSV");
    child->frmSmoothCurve(data);
    child->show();
}

