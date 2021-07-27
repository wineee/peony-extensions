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

#include <QStackedWidget>
#include <memory>

#include "preview-page-plugin-iface.h"
#include "file-info.h"
#include "file-watcher.h"

#include "base-preview-page.h"
#include "other-preview-page.h"
#include "audio-preview-page.h"

using Peony::FileWatcher;
using Peony::FileInfo;

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
    QString m_current_uri;
    PreviewPageIface::PreviewType m_current_type = PreviewPageIface::Other;

    QWidget *m_empty_tab_widget;
    BasePreviewPage *m_other_preview_widget;
    BasePreviewPage *m_preview_widget[5];

    std::shared_ptr<FileInfo> m_info;
    std::shared_ptr<FileWatcher> m_watcher;

    bool m_support = true;
};

#endif // CONTENTPREVIEWPAGE_H
