#include "previewpage/html.h"

HtmlPreviewPage::HtmlPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_web_page = new QWebEnginePage(this);
    m_web_channel = new QWebChannel(this);
    m_web_page->setWebChannel(m_web_channel);

    m_web_view = new QWebEngineView(this);
    m_web_view->setPage(m_web_page);
    m_web_view->setContentsMargins(0, 0, 0, 0);

    base_layout->addWidget(m_web_view);
}

void HtmlPreviewPage::cancel() {
    qDebug() << "HtmlPreviewPage::cancel: ";
    //m_web_view->close()
}

void HtmlPreviewPage::updateInfo(Peony::FileInfo *info) {
    qDebug() << "HtmlPreviewPage::updateInfo: " << info->filePath();
    m_web_page->load(QUrl(info->uri()));
}
