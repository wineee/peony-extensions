#include "pdf-preview-page.h"

PdfPreviewPage::PdfPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_document = new QPdfDocument(this);
    m_bookmarkModel = new QPdfBookmarkModel(this);
    m_bookmarkModel->setDocument(m_document);

    m_pdf_view = new QPdfView(this);
    m_pdf_view->setDocument(m_document);
    //m_pdf_view->setZoomMode(QPdfView::FitToWidth);
    m_pdf_view->setPageMode(QPdfView::MultiPage);

    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
    m_layout->addWidget(m_pdf_view);
}

void PdfPreviewPage::updateInfo(Peony::FileInfo *info) {
    m_document->load(info->filePath());
}

void PdfPreviewPage::cancel() {
    m_document->close();
}
