#include "previewpage/to-pdf.h"
#include "preview-file-type.h"

ToPdfPreviewPage::ToPdfPreviewPage(QWidget *parent):
    PdfPreviewPage(parent),m_proc(nullptr)
{

}

void ToPdfPreviewPage::cancel() {
    PdfPreviewPage::cancel();
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
            PdfPreviewPage::updateInfo(m_pdf_path);
        } else {
            qDebug() << QString("libreoffice crash exit with exitCode %1").arg(exitCode);
        }
    });
}
