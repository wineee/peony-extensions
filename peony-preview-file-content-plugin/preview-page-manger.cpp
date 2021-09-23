#include "preview-page-manger.h"

PreviewPageManger::PreviewPageManger(ContentPreviewPage *preview_page) :
    the_preview_page(preview_page),
    m_current_page(nullptr)
{

}

PreviewPageManger::~PreviewPageManger() {
    qDeleteAll(m_page_pool);
    m_page_pool.clear();
}

BasePreviewPage *PreviewPageManger::createPage(PreviewType cas) {
    switch (cas) {
    case PreviewType::Text:
        return new TextPreviewPage;
    case PreviewType::Audio:
        return new AudioPreviewPage;
    case PreviewType::Video:
        return new VideoPreviewPage;
    case PreviewType::Image:
        return new ImagePreviewPage;
    case PreviewType::Pdf:
        return new Pdf2PreviewPage;
    case PreviewType::OfficeDoc:
        //return new DocPreviewPage;
        return new ToPdfPreviewPage;
    default:
        return new OtherPreviewPage;
    }
}

void PreviewPageManger::startPreview(PreviewFileType *info) {
    auto type = info->getPreviewType();
    if (m_page_pool.contains(type)) {
        m_current_page = m_page_pool[type];
    } else {
        m_current_page = createPage(type);
        m_page_pool.insert(type, m_current_page);
        the_preview_page->addWidget(m_current_page);
    }
    m_current_page->updateInfo(info->m_info.get());
    the_preview_page->setCurrentWidget(m_current_page);
}

void PreviewPageManger::cancel() {
    if (m_current_page != nullptr)
        m_current_page->cancel();
}


