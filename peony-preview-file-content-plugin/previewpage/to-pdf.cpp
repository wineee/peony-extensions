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

#include "previewpage/to-pdf.h"
#include "preview-file-type.h"

ToPdfPreviewPage::ToPdfPreviewPage(QWidget *parent):
    ToPdfBaseClass(parent),m_proc(nullptr)
{

}

void ToPdfPreviewPage::cancel() {
    ToPdfBaseClass::cancel();
    if (m_proc != nullptr) {
        m_proc->deleteLater();
        m_proc = nullptr;
        QProcess::startDetached("rm", QStringList() << m_pdf_path);
    }
}

void ToPdfPreviewPage::updateInfo(Peony::FileInfo *info) {
    m_proc = new QProcess;
    m_proc->setProgram("libreoffice");
    m_proc->setArguments(QStringList() << "--headless" << "--invisible"
                       << "--convert-to" << "pdf"
                       << "--outdir" <<  "/tmp/peony/topdf"
                       << info->filePath());
    qDebug() << m_proc->arguments() << "\n" << info->filePath();
    m_proc->start();
    //m_proc->waitForFinished();
    connect(m_proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
          [=](int exitCode, QProcess::ExitStatus exitStatus) {
        if (exitStatus == QProcess::NormalExit) {
            QString file_name = info->displayName();
            file_name = file_name.left(file_name.lastIndexOf(".")) + ".pdf";
            m_pdf_path = QLatin1String("/tmp/peony/topdf/") + file_name;
            qDebug() << "new file:"+m_pdf_path;
            ToPdfBaseClass::updateInfo(m_pdf_path);
        } else {
            qDebug() << QString("libreoffice crash exit with exitCode %1").arg(exitCode);
        }
    });
}
