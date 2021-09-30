/*
 * Peony-Qt's Library
 *
 * Copyright (C) 2021, KylinSoft Co, Ltd.
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
 * Authors: Lu Hongxu <lhongxu@outlook.com>
 *
 */

#ifndef HTMLPREVIEWPAGE_H
#define HTMLPREVIEWPAGE_H

#include "previewpage/base.h"

#include <QWebChannel>
#include <QWebEngineView>
#include <QWebEnginePage>

class HtmlPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit HtmlPreviewPage(QWidget *parent = nullptr);
    ~HtmlPreviewPage() = default;

private:
    QWebEngineView *m_web_view;
    QWebChannel *m_web_channel;
    QWebEnginePage *m_web_page;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // HTMLPREVIEWPAGE_H
