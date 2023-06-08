
#ifndef CURVEMDI_H
#define CURVEMDI_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QPainterPath>
#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>


class SmoothCurve : public QLabel
{
    Q_OBJECT

public:

    SmoothCurve();
    QVector<QPointF> readDataFromCSV(const QString& filename);
    static QPainterPath createSmoothCurve(const QVector<QPointF> &points);
    void paintEvent(QPaintEvent *);
    void frmSmoothCurve(const QVector<QPointF>& data);

private:
    static void calculateFirstControlPoints(double *&result, const double *rhs, int n);
    static void calculateControlPoints(const QVector<QPointF> &datas,
                                       QVector<QPointF> *firstControlPoints,
                                       QVector<QPointF> *secondControlPoints);
    bool isUntitled;
    QVector<QPointF> datas;
    QLabel* curveWidget;
    QPainterPath pathNormal;    //正常曲线

};
#endif // CURVEMDI_H
