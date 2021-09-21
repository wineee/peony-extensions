#include "to-pdf.h"

#include "preview-file-type.h"
#include <QProcess>

ToPdfPreviewPage::ToPdfPreviewPage(QWidget *parent):
    PdfPreviewPage(parent)
{

}

void ToPdfPreviewPage::cancel() {
    PdfPreviewPage::cancel();
}

void ToPdfPreviewPage::updateInfo(Peony::FileInfo *info) {
    QProcess m_proc;
    m_proc.setProgram("libreoffice");
    m_proc.setArguments(QStringList() << "--headless" << "--invisible"
                       << "--convert-to" << "pdf"
                       << "--outdir" <<  "/tmp/peony/topdf"
                       << info->filePath());
    qDebug()<<m_proc.arguments();
    m_proc.start();
    if (m_proc.waitForFinished()) {
        // m_info(Peony::FileInfo::fromUri
        PdfPreviewPage::updateInfo(new PreviewFileType("file:///home/rewine/a.pdf"));
    }
}
