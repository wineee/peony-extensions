#include "preview-file-type.h"

#include <file-info-job.h>
#include <QDebug>

PreviewFileType::PreviewFileType(const QString &uri):
    m_info(Peony::FileInfo::fromUri(uri))
{
//    m_extension_name = getExtensionName();
//    m_preview_type = getPreviewType();
}

std::shared_ptr<PreviewFileType> PreviewFileType::fromUri(const QString &uri) {
    return std::make_shared<PreviewFileType>(uri);
}

QString PreviewFileType::getExtensionName() {
    for (int i = m_info->filePath().size()-1; i >= 0; i--)
        if (m_info->filePath().at(i) == '.')
            return m_info->filePath().right(m_info->filePath().size()-i-1);
    return QLatin1String("");
}

PreviewFileType::PreviewType PreviewFileType::getPreviewType() {
    const QString path = m_info->filePath();
    const QString type = m_info->fileType();
    const QString mimeType = m_info->mimeType();
    qDebug() << "Path :" << path << " \nType:" << type << "\n mimeType:"<<mimeType;

    // Prevent .ncm files from being recognized as Video
    if (type == "unknown")
        return Other;
    if (mimeType.startsWith("text") ||
            mimeType == "application/xml" ||
            mimeType == "application/json" ||
            mimeType == "application/javascript" ||
            mimeType == "application/vnd.nokia.qt.qmakeprofile")
        return Text;
    if (mimeType.startsWith("audio"))
        return Audio;
    if (m_info->isVideoFile())
        return Video;
    if (m_info->isImageFile())
        return Image;
    if (m_info->isPdfFile())
        return Pdf;
    if (m_info->isOfficeFile())
        return OfficeDoc;
    return Other;
}

void PreviewFileType::sync() {
    if (m_info->displayName().isEmpty()) {
        Peony::FileInfoJob j(m_info->uri());
        j.querySync();
    }
}
