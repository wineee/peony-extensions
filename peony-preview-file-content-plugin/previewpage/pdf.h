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

#ifndef PDFPREVIEWPAGE_H
#define PDFPREVIEWPAGE_H

#include "previewpage/base.h"

#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfView>
//#include <QPdfPageRenderer>
//#include <QtPdf>

/*
class QPdfWidget : public QPdfView {
    Q_OBJECT
public:
    explicit QPdfWidget(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};
*/

class PdfPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit PdfPreviewPage(QWidget *parent = nullptr);
    ~PdfPreviewPage() = default;

private Q_SLOTS:
    void onCurrentPageChanged(int page);
    void pageNumberEdited();

private:
    QPdfDocument *m_document;
    QPdfBookmarkModel *m_bookmark_model;
    QPdfView *m_pdf_view;
    //QPdfPageRenderer *m_page_renderer;
    //QPdfPageNavigation *m_page_navigation;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
    void updateInfo(QString path);
};

#endif // PDFPREVIEWPAGE_H
