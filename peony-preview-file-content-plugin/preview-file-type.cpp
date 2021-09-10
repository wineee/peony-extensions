#include "preview-file-type.h"

#include <file-info-job.h>

PreviewFileType::PreviewFileType(const QString &uri):
    m_info(Peony::FileInfo::fromUri(uri))
{
    m_extension_name = getExtensionName();
    m_preview_type = getPreviewType();
}

std::shared_ptr<PreviewFileType> PreviewFileType::fromUri(const QString &uri) {
    return  std::make_shared<PreviewFileType>(uri);
}


QString PreviewFileType::getExtensionName() {
    for (int i = m_info->filePath().size()-1; i >= 0; i--)
        if (m_info->filePath().at(i) == '.')
            return m_info->filePath().right(m_info->filePath().size()-i-1);
    return QLatin1String("");
}

PreviewFileType::PreviewType PreviewFileType::getPreviewType() {

}

void PreviewFileType::sync() {
    if (m_info->displayName().isEmpty()) {
        Peony::FileInfoJob j(m_info->uri());
        j.querySync();
    }
}
