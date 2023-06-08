#include "curveMdi.h"
#include <QPainterPath>
#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <QPointF>
#include <QLabel>


SmoothCurve::SmoothCurve()
{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
//     创建 QLabel 用于显示视频流
    curveWidget  = new QLabel(this);
    curveWidget ->setAlignment(Qt::AlignCenter);

    // 创建垂直布局，并将 QLabel 添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(curveWidget);

    curveWidget->setFixedSize(200, 150);

    layout->setContentsMargins(0, 0, 0, 0);

    // 设置子窗口的布局
    setLayout(layout);


}

QVector<QPointF> SmoothCurve::readDataFromCSV(const QString& filename)
{
    QVector<QPointF> data;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList values = line.split(',');

            // Assuming the CSV format is: x,y
            if (values.size() >= 2)
            {
                bool xOk, yOk;
                qreal x = values[0].toDouble(&xOk);
                qreal y = values[1].toDouble(&yOk);
                if (xOk && yOk)
                {
                    data.append(QPointF(x, y));
                }
            }
        }

        file.close();
    }

    return data;
}

QPainterPath SmoothCurve::createSmoothCurve(const QVector<QPointF> &points)
{
    QPainterPath path;
    int len = points.count();
    if (len < 2) {
        return path;
    }

    QVector<QPointF> firstControlPoints;
    QVector<QPointF> secondControlPoints;
    calculateControlPoints(points, &firstControlPoints, &secondControlPoints);
    path.moveTo(points[0].x(), points[0].y());

    for (int i = 0; i < len - 1; ++i) {
        path.cubicTo(firstControlPoints[i], secondControlPoints[i], points[i + 1]);
    }

    return path;
}

void SmoothCurve::calculateFirstControlPoints(double *&result, const double *rhs, int n)
{
    result = new double[n];
    double *tmp = new double[n];
    double b = 2.0;
    result[0] = rhs[0] / b;

    for (int i = 1; i < n; ++i) {
        tmp[i] = 1 / b;
        b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
        result[i] = (rhs[i] - result[i - 1]) / b;
    }

    for (int i = 1; i < n; ++i) {
        result[n - i - 1] -= tmp[n - i] * result[n - i];
    }

    delete tmp;
}

void SmoothCurve::calculateControlPoints(const QVector<QPointF> &datas,
                                         QVector<QPointF> *firstControlPoints,
                                         QVector<QPointF> *secondControlPoints)
{
    int n = datas.count() - 1;
    for (int i = 0; i < n; ++i) {
        firstControlPoints->append(QPointF());
        secondControlPoints->append(QPointF());
    }

    if (n == 1) {
        (*firstControlPoints)[0].rx() = (2 * datas[0].x() + datas[1].x()) / 3;
        (*firstControlPoints)[0].ry() = (2 * datas[0].y() + datas[1].y()) / 3;
        (*secondControlPoints)[0].rx() = 2 * (*firstControlPoints)[0].x() - datas[0].x();
        (*secondControlPoints)[0].ry() = 2 * (*firstControlPoints)[0].y() - datas[0].y();
        return;
    }

    double *xs = 0;
    double *ys = 0;
    double *rhsx = new double[n];
    double *rhsy = new double[n];

    for (int i = 1; i < n - 1; ++i) {
        rhsx[i] = 4 * datas[i].x() + 2 * datas[i + 1].x();
        rhsy[i] = 4 * datas[i].y() + 2 * datas[i + 1].y();
    }

    rhsx[0] = datas[0].x() + 2 * datas[1].x();
    rhsx[n - 1] = (8 * datas[n - 1].x() + datas[n].x()) / 2.0;
    rhsy[0] = datas[0].y() + 2 * datas[1].y();
    rhsy[n - 1] = (8 * datas[n - 1].y() + datas[n].y()) / 2.0;

    calculateFirstControlPoints(xs, rhsx, n);
    calculateFirstControlPoints(ys, rhsy, n);

    for (int i = 0; i < n; ++i) {
        (*firstControlPoints)[i].rx() = xs[i];
        (*firstControlPoints)[i].ry() = ys[i];

        if (i < n - 1) {
            (*secondControlPoints)[i].rx() = 2 * datas[i + 1].x() - xs[i + 1];
            (*secondControlPoints)[i].ry() = 2 * datas[i + 1].y() - ys[i + 1];
        } else {
            (*secondControlPoints)[i].rx() = (datas[n].x() + xs[n - 1]) / 2;
            (*secondControlPoints)[i].ry() = (datas[n].y() + ys[n - 1]) / 2;
        }
    }

    delete xs;
    delete ys;
    delete rhsx;
    delete rhsy;
}

void SmoothCurve::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(1, -1);

    // Draw coordinate axis
    painter.setPen(QColor(180, 180, 180));
    painter.drawLine(-250, 0, 250, 0);
    painter.drawLine(0, 150, 0, -150);

    // Draw the smooth curve path
    painter.setPen(QPen(QColor(80, 80, 80), 2));
    painter.drawPath(pathNormal);

    // If the points on the curve are visible, draw them
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    foreach (QPointF point, datas) {
        painter.drawEllipse(point, 3, 3);
    }

}


void SmoothCurve::frmSmoothCurve(const QVector<QPointF>& data)
{
    pathNormal = createSmoothCurve(data);
    update();  // Trigger a repaint of the child window
}
