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

#ifndef PDF2PREVIEWPAGE_H
#define PDF2PREVIEWPAGE_H

#include "previewpage/base.h"
#include "QPdfWidget"

class Pdf2PreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit Pdf2PreviewPage(QWidget *parent = nullptr);
    ~Pdf2PreviewPage() = default;

private:
    QPdfWidget *m_pdf_widget;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
    void updateInfo(QString path);
};

#endif // PDF2PREVIEWPAGE_H
