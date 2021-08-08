#include "doc-preview-page.h"
#include <QVBoxLayout>

DocPreviewPage::DocPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_web_view = new QWebEngineView(this);
    m_web_view->setUrl(QUrl("qrc:/index.html"));

    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
    m_layout->addWidget(m_web_view);
}

void DocPreviewPage::cancel() {

}

void DocPreviewPage::updateInfo(Peony::FileInfo *info) {

}
