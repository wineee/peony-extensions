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
#include <file-watcher.h>

#include "preview-page-plugin-iface.h"
#include "preview-file-type.h"

class PreviewPageManger;

class ContentPreviewPage : public QStackedWidget, public Peony::PreviewPageIface
{
    Q_OBJECT
public:
    explicit ContentPreviewPage(QWidget *parent = nullptr);
    ~ContentPreviewPage() override;
    void prepare(const QString &uri, PreviewType type){

    }
    void prepare(const QString &uri) override;
    void startPreview() override;
    void cancel() override;
    void closePreviewPage() override {
        deleteLater();
    }

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QString m_current_uri;
    //PreviewType m_current_type = PreviewPageIface::Other;
    PreviewPageManger *m_page_manger = nullptr;

    QWidget *m_empty_tab_widget;
    std::shared_ptr<PreviewFileType> m_file_info;
    std::shared_ptr<Peony::FileWatcher> m_watcher;

    bool m_support = true;
};

#endif // CONTENTPREVIEWPAGE_H
