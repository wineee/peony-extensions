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

#ifndef CONTENTPREVIEWPAGE_H
#define CONTENTPREVIEWPAGE_H

#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QIcon>

#include <QFile>
#include <QFileInfo>
#include <QUrl>

#include <memory>

#include "peony-qt/preview-page-plugin-iface.h"
#include "peony-qt/file-info.h"
#include "peony-qt/controls/icon-container.h"

using namespace Peony;

class FilePreviewPage;

class ContentPreviewPage : public QStackedWidget, public Peony::PreviewPageIface
{
    Q_OBJECT
public:
    explicit ContentPreviewPage(QWidget *parent = nullptr);
    ~ContentPreviewPage() override;

    void prepare(const QString &uri, PreviewType type) override;
    void prepare(const QString &uri) override;
    void startPreview() override;
    void cancel() override;
    void closePreviewPage() override {
        deleteLater();
    }

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void paintEvent(QPaintEvent *e) override;

private:
    //QLabel *m_label = nullptr;
    QString m_current_uri;
    Peony::PreviewPageIface::PreviewType m_current_type = Peony::PreviewPageIface::Other;

    QWidget *m_empty_tab_widget;
    FilePreviewPage *m_preview_tab_widget;
    std::shared_ptr<FileInfo> m_info;
    //std::shared_ptr<FileWatcher> m_watcher;

    bool m_support = true;
};


class FilePreviewPage : public QFrame
{
    friend class ContentPreviewPage;
    Q_OBJECT
private:
    explicit FilePreviewPage(QWidget *parent = nullptr);
    ~FilePreviewPage();

private Q_SLOTS:
    void updateInfo(FileInfo *info);
    void resizeIcon(QSize size);

private:
    QGridLayout *m_layout;
    //IconContainer *m_icon;
    QFormLayout *m_form;
    QLabel *m_display_name_label;
    QLabel *m_type_label;
    QLabel *m_time_modified_label;
    QLabel *m_time_access_label;

    //image
    QLabel *m_image_size;
    QLabel *m_image_format;
};

#endif // CONTENTPREVIEWPAGE_H
