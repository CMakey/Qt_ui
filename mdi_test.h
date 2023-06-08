
#ifndef MDI_TEST_H
#define MDI_TEST_H

#include <QMainWindow>
#include <QMdiArea>
#include <QButtonGroup>

class TableMdiChild;
class VideoMdiChild;
class SmoothCurve;

QT_BEGIN_NAMESPACE
namespace Ui { class mdi_test; }
QT_END_NAMESPACE

class mdi_test : public QMainWindow

{
    Q_OBJECT

public:
    mdi_test(QWidget *parent = nullptr);
    ~mdi_test();


private:
    Ui::mdi_test *ui;
    QMdiArea *mdiArea;
    QVector<QPointF> m_curveData;
    QString imagePath;
    QString csv_path;
//    QVector<QPointF> readDataFromCSV(const QString& filename);
    QButtonGroup btnGroup;

private slots:
    void on_actionnew_table_triggered();
    void on_actionnew_video_triggered();
    void on_actionnew_curve_triggered();
};

#endif // MDI_TEST_H
