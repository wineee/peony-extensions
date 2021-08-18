#include "pdf-preview-page.h"

PdfPreviewPage::PdfPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_document = new QPdfDocument(this);
    m_bookmark_model = new QPdfBookmarkModel(this);
    m_bookmark_model->setDocument(m_document);
    m_pdf_view = new QPdfView(this);
    m_pdf_view->setDocument(m_document);
    m_pdf_view->setZoomMode(QPdfView::CustomZoom); // FitInView
    m_pdf_view->setPageMode(QPdfView::MultiPage);
//    m_page_renderer = new QPdfPageRenderer;
//    m_page_renderer->setDocument(m_document);
//    m_page_renderer->setRenderMode(Qt::MultiThreaded);
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_pdf_view);
    setLayout(m_layout);
}

void PdfPreviewPage::updateInfo(Peony::FileInfo *info) {
    m_document->load(info->filePath());
}

void PdfPreviewPage::cancel() {
    m_document->close();
}
