#include "image-preview-page.h"

#include <QImageReader>

ImagePreviewPage::ImagePreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_image_scene  = new QGraphicsScene;
    m_image_item = new QGraphicsPixmapItem;
    m_image_view = new QGraphicsView;
    m_image_view->setScene(m_image_scene);

    m_horizontal_flip_button = new QPushButton(this);
    m_horizontal_flip_button->setText("水平翻转");
    connect(m_horizontal_flip_button, &QPushButton::clicked, this, &ImagePreviewPage::doHorizontalFlip);

    m_vertical_flip_button = new QPushButton(this);
    m_vertical_flip_button->setText("垂直翻转");
    connect(m_vertical_flip_button, &QPushButton::clicked, this, &ImagePreviewPage::doVerticalFlip);

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_image_view);
    m_layout->addWidget(m_horizontal_flip_button);
    m_layout->addWidget(m_vertical_flip_button);
    setLayout(m_layout);
}

void ImagePreviewPage::updateInfo(Peony::FileInfo *info) {
    QPixmap newPixmap(info->filePath());
    m_image_item = m_image_scene->addPixmap(newPixmap);
    m_image_scene->setSceneRect(QRectF(newPixmap.rect()));
}

void ImagePreviewPage::cancel() {
    m_image_scene->clear();
    m_image_view->resetTransform();
}

void ImagePreviewPage::paintEvent(QPaintEvent *event) {
    m_image_view->resetTransform();
    int height = m_image_item->pixmap().height();
    int width = m_image_item->pixmap().width();
    int max_height = m_image_view->height();
    int max_width = m_image_view->width();
    int pic_size = qMax(width, height);
    int max_size = qMin(max_width, max_height) - 5;
    double val = static_cast<double>(max_size) / pic_size;
    m_image_view->scale(val, val);
}

void ImagePreviewPage::doHorizontalFlip() {
    QImage origin = m_image_item->pixmap().toImage();
    QImage newImage = QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int i = 0; i < newImage.width(); ++i) {
        for (int j = 0; j < newImage.height(); ++j) {
            tmpColor = QColor(origin.pixel(i, j));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();
            newImage.setPixel(newImage.width()-i-1, j, qRgb(r,g,b));
        }
    }
    QPixmap newPixmap;
    newPixmap.convertFromImage(newImage);
    m_image_item->setPixmap(newPixmap);
    m_image_scene->setSceneRect(QRectF(newPixmap.rect()));
}

void ImagePreviewPage::doVerticalFlip() {
    QImage origin = m_image_item->pixmap().toImage();
    QImage newImage = QImage(QSize(origin.width(), origin.height()),
                                  QImage::Format_ARGB32);
    QColor tmpColor;
    int r, g, b;
    for (int i = 0; i < newImage.width(); ++i) {
        for (int j = 0; j < newImage.height(); ++j) {
            tmpColor = QColor(origin.pixel(i, j));
            r = tmpColor.red();
            g = tmpColor.green();
            b = tmpColor.blue();
            newImage.setPixel(i, newImage.height()-j-1, qRgb(r,g,b));
        }
    }
    QPixmap newPixmap;
    newPixmap.convertFromImage(newImage);
    m_image_item->setPixmap(newPixmap);
    m_image_scene->setSceneRect(QRectF(newPixmap.rect()));
}

