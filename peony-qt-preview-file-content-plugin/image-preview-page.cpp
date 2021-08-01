#include "image-preview-page.h"

#include <QImageReader>

ImagePreviewPage::ImagePreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_image_label = new QLabel(this);
    m_image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_image_label->setScaledContents(true);

    m_scroll_area = new QScrollArea(this);
    m_scroll_area->setWidget(m_image_label);
    m_scroll_area->setWidgetResizable(true);

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_scroll_area);
    setLayout(m_layout);
}

void ImagePreviewPage::updateInfo(Peony::FileInfo *info) {
    QImageReader reader(info->filePath());
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    m_image_label->setPixmap(QPixmap::fromImage(newImage));
}

void ImagePreviewPage::cancel() {

}
