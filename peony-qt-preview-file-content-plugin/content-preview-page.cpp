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
#include <QResizeEvent>

#include <QDebug>

ContentPreviewPage::ContentPreviewPage(QWidget *parent) : QStackedWidget(parent)
{
    qDebug() << "Init ContentPreviewPage";

    setContentsMargins(10, 0, 10, 0);
    auto label = new QLabel(tr("Select the file you want to preview..."), this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    m_empty_tab_widget = label;

    auto previewPage = new OtherPreviewPage(this);
    previewPage->installEventFilter(this);
    m_other_preview_widget = previewPage;

 //   addWidget(m_other_preview_widget);
 //   addWidget(m_empty_tab_widget);

    setCurrentWidget(m_empty_tab_widget);
}

ContentPreviewPage::~ContentPreviewPage()
{
    cancel();
}

void ContentPreviewPage::prepare(const QString &uri, PreviewType type) {
    qDebug() << "prepare: " << uri << " " << type;
    m_current_uri = uri;
    m_current_type = type;

    m_info = FileInfo::fromUri(uri);
    m_support = uri.contains("file:///");
}

void ContentPreviewPage::prepare(const QString &uri) {
    prepare(uri, PreviewType::Other);
}

void ContentPreviewPage::startPreview() {
    qDebug() << "startPreview ";
    if (m_support) {
        auto previewPage = qobject_cast<OtherPreviewPage*>(m_other_preview_widget);
        previewPage->updateInfo(m_info.get());
        setCurrentWidget(previewPage);
    } else {
        QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
        label->setText(tr("Can not preview this file."));
    }
}

void ContentPreviewPage::cancel() {
    qDebug() << "cancel ";
    setCurrentWidget(m_empty_tab_widget);
    QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
    label->setText(tr("Select the file you want to preview..."));
}

bool ContentPreviewPage::eventFilter(QObject *obj, QEvent *ev) {
    if (obj == m_other_preview_widget) {
        if (ev->type() == QEvent::Resize) {
            auto e = static_cast<QResizeEvent*>(ev);
            auto page = qobject_cast<OtherPreviewPage*>(m_other_preview_widget);
            int width = e->size().width() - 50;
            width = qMax(width, 96);
            width = qMin(width, 256);
            page->resizeIcon(QSize(width, width * 2/3));
        }
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
