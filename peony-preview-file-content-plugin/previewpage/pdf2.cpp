#include "previewpage/pdf2.h"

Pdf2PreviewPage::Pdf2PreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_pdf_widget = new QPdfWidget(this);
    m_pdf_widget->showFullScreen();
    base_layout->addWidget(m_pdf_widget);
}

void Pdf2PreviewPage::cancel() {
    m_pdf_widget->closeDocument();
}

void Pdf2PreviewPage::updateInfo(Peony::FileInfo *info) {
    m_pdf_widget->loadFile(info->filePath());
}

void Pdf2PreviewPage::updateInfo(QString path) {
    m_pdf_widget->loadFile(path);
}
