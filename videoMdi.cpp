

#include <QtWidgets>

#include "videoMdi.h"

VideoMdiChild::VideoMdiChild()
{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
    // 创建 QLabel 用于显示视频流
    m_videoLabel = new QLabel(this);
    m_videoLabel->setAlignment(Qt::AlignCenter);

    // 创建垂直布局，并将 QLabel 添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_videoLabel);
//    m_videoLabel->setFixedSize(400, 300);//设置窗口初始大小
//    m_videoLabel->setScaledContents(true);    //根据label大小缩放图片
    m_videoLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_videoLabel->setScaledContents(true);
    m_videoLabel->setMinimumSize(400, 300);


    layout->setContentsMargins(0, 0, 0, 0);

    // 设置子窗口的布局
    setLayout(layout);
}

//void VideoMdiChild::setVideoFrame(const QImage &frame)
//{

//    // 在 QLabel 中显示视频帧
//    m_videoLabel->setPixmap(QPixmap::fromImage(frame));
//}
//QString VideoMdiChild::setImagePath(const QString& path)
//{
//    return imagePath = path;
//}
QString VideoMdiChild::setImagePath()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Image Files (*.png *.jpg *.bmp *.tif *.tiff)");

    if (!imagePath.isEmpty())
    {
        // 在这里进行相关处理，例如加载并显示图片
        QImage image(imagePath);
        // 处理显示逻辑，例如将图片显示在 QLabel 控件中
        // QLabel *imageLabel = new QLabel(this);
        // imageLabel->setPixmap(QPixmap::fromImage(image));
        // imageLabel->show();
    }

    return imagePath;
}


void VideoMdiChild::showImage(const QString& imagePath)
{

    // 在 QLabel 中显示视频帧
    QPixmap pixmap(imagePath);
    m_videoLabel->setPixmap(pixmap);
    // 检查图像是否成功加载
    if (!pixmap.isNull()) {
        // 根据图像大小自动调整 QLabel 大小
        m_videoLabel->setPixmap(pixmap.scaled(m_videoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//        m_videoLabel->setPixmap(QPixmap::fromImage(m_videoLabel));

    } else {
        // 图像加载失败时显示错误信息
        m_videoLabel->setText("Failed to load image");
    }
}

