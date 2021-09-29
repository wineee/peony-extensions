#ifndef PREVIEWPAGEMANGER_H
#define PREVIEWPAGEMANGER_H

#include "previewpage/other.h"
#include "previewpage/audio.h"
#include "previewpage/text.h"
#include "previewpage/video.h"
#include "previewpage/image.h"
#include "previewpage/html.h"
#include "previewpage/pdf2.h"
#include "previewpage/to-pdf.h"
#ifdef USE_QTPDF
#include "previewpage/pdf.h"
#endif
#ifdef USE_OnlyOffice
#include "previewpage/onlyoffice.h"
#endif

#include "content-preview-page.h"
#include "preview-file-type.h"

#include <QMap>

class PreviewPageManger
{
    typedef PreviewFileType::PreviewType PreviewType;
public:
    PreviewPageManger() = delete;
    explicit PreviewPageManger(ContentPreviewPage *preview_page);
    ~PreviewPageManger();

public:
    void cancel();
    void startPreview(PreviewFileType *info);

private:
    BasePreviewPage *createPage(PreviewType cas);

private:
    ContentPreviewPage *the_preview_page;

    QMap<PreviewType, BasePreviewPage *> m_page_pool;
    BasePreviewPage *m_current_page;
};

#endif // PREVIEWPAGEMANGER_H
