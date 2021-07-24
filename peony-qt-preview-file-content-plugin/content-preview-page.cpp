/*
 * Peony-Qt's Library
 *
 * Copyright (C) 2019, Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#include "content-preview-page.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QPainter>

#include <QLabel>

#include <QUrl>
#include <QMimeDatabase>
#include <QLocale>
#include <QDateTime>
#include <QResizeEvent>
#include <QImageReader>

#include "peony-qt/thumbnail-manager.h"
#include "peony-qt/file-info-job.h"

ContentPreviewPage::ContentPreviewPage(QWidget *parent) : QStackedWidget(parent)
{
    setContentsMargins(10, 0, 10, 0);
    auto label = new QLabel(tr("Select the file you want to preview..."), this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    m_empty_tab_widget = label;

    auto previewPage = new FilePreviewPage(this);
    previewPage->installEventFilter(this);
    m_preview_tab_widget = previewPage;

    addWidget(m_preview_tab_widget);
    addWidget(m_empty_tab_widget);

    setCurrentWidget(m_empty_tab_widget);
}

ContentPreviewPage::~ContentPreviewPage()
{
    cancel();
}

void ContentPreviewPage::prepare(const QString &uri, PreviewType type) {
    m_current_uri = uri;
    m_current_type = type;

    m_info = FileInfo::fromUri(uri);
    m_support = uri.contains("file:///");
}

void ContentPreviewPage::prepare(const QString &uri) {
    prepare(uri, PreviewType::Other);
}

void ContentPreviewPage::startPreview() {
    if (m_support) {
        auto previewPage = qobject_cast<FilePreviewPage*>(m_preview_tab_widget);
        previewPage->updateInfo(m_info.get());
        setCurrentWidget(previewPage);
    } else {
        QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
        label->setText(tr("Can not preview this file."));
    }
}

void ContentPreviewPage::cancel() {
    //m_preview_tab_widget->cancel();
    setCurrentWidget(m_empty_tab_widget);
    QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
    label->setText(tr("Select the file you want to preview..."));
}

bool ContentPreviewPage::eventFilter(QObject *obj, QEvent *ev) {
    if (obj == m_preview_tab_widget) {
//        if (ev->type() == QEvent::Resize) {
//            auto e = static_cast<QResizeEvent*>(ev);
//            auto page = qobject_cast<FilePreviewPage*>(m_preview_tab_widget);
//            int width = e->size().width() - 50;
//            width = qMax(width, 96);
//            width = qMin(width, 256);
//            page->resizeIcon(QSize(width, width * 2/3));
//        }
    }
    return QWidget::eventFilter(obj, ev);
}

void ContentPreviewPage::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(this->rect(), this->palette().base());
    QWidget::paintEvent(e);
}

////////////////////////


FilePreviewPage::FilePreviewPage(QWidget *parent) : QFrame(parent)
{
    m_layout = new QGridLayout(this);
    setLayout(m_layout);

//    m_icon = new IconContainer(this);
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

FilePreviewPage::~FilePreviewPage()
{

}

void FilePreviewPage::updateInfo(FileInfo *info)
{
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
    //m_icon->setIcon(thumbnail.isNull()? icon: thumbnail);
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
        QUrl url = info->uri();
        QImageReader r(url.path());
        auto image_size_row_left = m_form->itemAt(4, QFormLayout::LabelRole)->widget();
        image_size_row_left->setVisible(true);

        m_image_size->setText(tr("%1x%2").arg(r.size().width()).arg(r.size().height()));
        auto thumbnail = ThumbnailManager::getInstance()->tryGetThumbnail(info->uri());
        bool rgba = thumbnail.pixmap(r.size()).hasAlphaChannel();
        m_image_size->setVisible(true);
        auto image_format_row_left = m_form->itemAt(5, QFormLayout::LabelRole)->widget();
        image_format_row_left->setVisible(true);
        m_image_format->setText(rgba? "RGBA": "RGB");
        m_image_format->setVisible(true);
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

void FilePreviewPage::resizeIcon(QSize size)
{
    //m_icon->setIconSize(size);
}
