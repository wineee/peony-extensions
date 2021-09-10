#ifndef PREVIEWPAGEMANGER_H
#define PREVIEWPAGEMANGER_H

#include "previewpage/other.h"
#include "previewpage/audio.h"
#include "previewpage/text.h"
#include "previewpage/pdf.h"
#include "previewpage/video.h"
#include "previewpage/image.h"
#include "previewpage/onlyoffice.h"
#include "previewpage/html.h"

#include "content-preview-page.h"
#include "preview-file-type.h"

#include <QMap>

class PreviewPageManger
{
public:
    PreviewPageManger() = delete;
    explicit PreviewPageManger(ContentPreviewPage *preview_page);
    ~PreviewPageManger();

public:
    void cancel();
    void startPreview(PreviewFileType *info);
private:
    ContentPreviewPage *m_preview_page;

    QMap<PreviewFileType::PreviewType, BasePreviewPage *> m_page_pool;
    BasePreviewPage *m_current_page;
};

#endif // PREVIEWPAGEMANGER_H
