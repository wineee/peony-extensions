#include "preview-page-manger.h"

PreviewPageManger::PreviewPageManger(ContentPreviewPage *preview_page) :
    m_preview_page(preview_page),
    m_current_page(nullptr)
{

}

PreviewPageManger::~PreviewPageManger() {
    qDeleteAll(m_page_pool);
    m_page_pool.clear();
}

void PreviewPageManger::startPreview(PreviewFileType *info) {
    if (m_page_pool.contains(PreviewFileType::Other)) {
        m_current_page = m_page_pool[PreviewFileType::Other];
    } else {
        m_current_page = new OtherPreviewPage;
        m_page_pool.insert(PreviewFileType::Other, m_current_page);
        m_preview_page->addWidget(m_current_page);
    }
    m_current_page->updateInfo(info->m_info.get());
    m_preview_page->setCurrentWidget(m_current_page);
}

void PreviewPageManger::cancel() {
    if (m_current_page != nullptr)
        m_current_page->cancel();
}


