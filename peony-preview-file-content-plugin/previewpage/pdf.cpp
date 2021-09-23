#include "previewpage/pdf.h"

#include <QtPdfWidgets>
/*
QPdfWidget::QPdfWidget(QWidget *parent) : QPdfView(parent) {
     setWindowFlags(Qt::FramelessWindowHint);
}

void QPdfWidget::resizeEvent(QResizeEvent *event) {
//    QPdfView tmp = *this;
//    tmp.resizeEvent(event);
//    *this = qobject_cast<QPdfWidget>(tmp);
     QPdfView::resizeEvent(event);
     qDebug() << event->size() << " " << this->zoomFactor();
}
*/
PdfPreviewPage::PdfPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
//    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
//    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    m_document = new QPdfDocument(this);
    m_bookmark_model = new QPdfBookmarkModel(this);
    m_bookmark_model->setDocument(m_document);
    m_pdf_view = new QPdfView(this);
    m_pdf_view->setDocument(m_document);
    m_pdf_view->setZoomMode(QPdfView::FitInView);
    m_pdf_view->setPageMode(QPdfView::MultiPage);
/*
    m_page_renderer = new QPdfPageRenderer;
    m_page_renderer->setDocument(m_document);
    m_page_renderer->setRenderMode(QPdfPageRenderer::RenderMode::MultiThreaded);
*/
    base_layout->addWidget(m_pdf_view);
}

void PdfPreviewPage::updateInfo(Peony::FileInfo *info) {
    m_document->load(info->filePath());
}

void PdfPreviewPage::updateInfo(QString path) {
    m_document->load(path);
}

void PdfPreviewPage::cancel() {
    m_document->close();
}
