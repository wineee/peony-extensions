#include "image-preview-page.h"

#include <QImageReader>

ImagePreviewPage::ImagePreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
//    m_image_label = new QLabel(this);
//    m_image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    m_image_label->setScaledContents(true);

//    m_scroll_area = new QScrollArea(this);
//    m_scroll_area->setWidget(m_image_label);
//    m_scroll_area->setWidgetResizable(true);

    m_image_scene  = new QGraphicsScene;
    m_image_item = new QGraphicsPixmapItem;
    m_image_view = new QGraphicsView;
    m_image_view->setScene(m_image_scene);

    m_layout = new QVBoxLayout(this);
    //m_layout->addWidget(m_scroll_area);
    m_layout->addWidget(m_image_view);
    setLayout(m_layout);
}

void ImagePreviewPage::updateInfo(Peony::FileInfo *info) {
    //QImageReader reader(info->filePath());
    //reader.setAutoTransform(true);
    //const QImage newImage = reader.read();
    //m_image_label->setPixmap(QPixmap::fromImage(newImage));

    QPixmap newPixmap(info->filePath());
    m_image_item = m_image_scene->addPixmap(newPixmap);
    m_image_scene->setSceneRect(QRectF(newPixmap.rect()));

    m_image_view->resetTransform();

    int height = m_image_item->pixmap().height();
    int width = m_image_item->pixmap().width();
    int max_height = m_image_view->height();
    int max_width = m_image_view->width();
    int pic_size = qMax(width, height);
    int max_size = qMin(max_width, max_height) - 5;
    double val = (max_size * 1.0) / pic_size;
    m_image_view->scale(val, val);
}

void ImagePreviewPage::cancel() {

}
