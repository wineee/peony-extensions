#include "previewpage/pdf2.h"
#include <QDir>
#include <QtWebEngine>

Pdf2PreviewPage::Pdf2PreviewPage(QWidget *parent) : BasePreviewPage(parent)
{

    m_pdf_widget = new QPdfWidget(this);
    m_pdf_widget->showFullScreen();
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_pdf_widget);
    setLayout(m_layout);
}

void Pdf2PreviewPage::cancel() {
    m_pdf_widget->closeDocument();
}

void Pdf2PreviewPage::updateInfo(Peony::FileInfo *info) {
    m_pdf_widget->loadFile(info->filePath());
}
