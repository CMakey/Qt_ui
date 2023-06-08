
#ifndef VIDEOMDI_H
#define VIDEOMDI_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class VideoMdiChild : public QWidget
{
    Q_OBJECT

public:

    VideoMdiChild();
//    void setVideoFrame(const QImage &frame);
    void showImage(const QString& imagePath);
//    QString setImagePath(const QString& path);
    QString setImagePath();



private:
    QLabel *m_videoLabel;
    bool isUntitled;
    QString imagePath;

};

#endif // VIDEOMDI_H
