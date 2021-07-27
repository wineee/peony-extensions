#include "other-preview-page.h"

#include <QDebug>
#include <QDateTime>
#include <QImageReader>

OtherPreviewPage::OtherPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    qDebug() << "init OtherPreviewPage";
    m_layout = new QGridLayout(this);
    setLayout(m_layout);
//    m_icon = new Peony::IconContainer(nullptr);
//    m_icon->setIconSize(QSize(96, 96));
//    m_layout->addWidget(m_icon);
    m_form = new QFormLayout(this);
    m_display_name_label = new QLabel(this);
    m_display_name_label->setWordWrap(true);
    m_form->addRow(tr("File Name:"), m_display_name_label);
    m_type_label = new QLabel(this);
    m_form->addRow(tr("File Type:"), m_type_label);
    m_time_access_label = new QLabel(this);
    m_form->addRow(tr("Time Access:"), m_time_access_label);
    m_time_modified_label = new QLabel(this);
    m_form->addRow(tr("Time Modified:"), m_time_modified_label);

    //image
    m_image_size = new QLabel(this);
    m_form->addRow(tr("Image size:"), m_image_size);
    m_image_format = new QLabel(this);
    m_form->addRow(tr("Image format:"), m_image_format);

    m_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    m_form->setFormAlignment(Qt::AlignHCenter);
    m_form->setLabelAlignment(Qt::AlignRight);

    QWidget *form = new QWidget(this);
    form->setLayout(m_form);
    m_layout->addWidget(form, 1, 0);
}

void OtherPreviewPage::updateInfo(FileInfo *info)
{
    qDebug() << "FilePreviewPage::updateInfo";
    if (info->displayName().isEmpty()) {
        FileInfoJob j(info->uri());
        j.querySync();
    }
    auto thumbnail = ThumbnailManager::getInstance()->tryGetThumbnail(info->uri());
    if (!thumbnail.isNull()) {
        QUrl url = info->uri();
        thumbnail.addFile(url.path());
    }
    //auto icon = QIcon::fromTheme(info->iconName(), QIcon::fromTheme("text-x-generic"));
    m_display_name_label->setText(info->displayName());
    m_type_label->setText(info->fileType());

    QLocale locale;
    auto access = QDateTime::fromMSecsSinceEpoch(info->accessTime()*1000);
    auto modify = QDateTime::fromMSecsSinceEpoch(info->modifiedTime()*1000);

    m_time_access_label->setText(access.toString(Qt::SystemLocaleShortDate));
    m_time_modified_label->setText(modify.toString(Qt::SystemLocaleShortDate));

    if (info->isDir()) {

    }

    if (info->mimeType().startsWith("image/")) {

    } else {
        auto image_size_row_left = m_form->itemAt(4, QFormLayout::LabelRole)->widget();
        image_size_row_left->setVisible(false);
        m_image_size->setVisible(false);
        auto image_format_row_left = m_form->itemAt(5, QFormLayout::LabelRole)->widget();
        image_format_row_left->setVisible(false);
        m_image_format->setVisible(false);
    }
    if (info->fileType().startsWith("video/")) {

    }
    if (info->fileType().startsWith("audio/")) {

    }
}

void OtherPreviewPage::resizeIcon(QSize size)
{
    //m_icon->setIconSize(size);
}

void OtherPreviewPage::cancel() {

}
