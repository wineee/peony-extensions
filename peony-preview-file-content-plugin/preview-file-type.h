#ifndef PREVIEWFILETYPE_H
#define PREVIEWFILETYPE_H

#include <QString>
#include <file-info.h>

class PreviewFileType
{
    friend class PreviewPageManger;
public:
    explicit PreviewFileType(const QString &uri);

    enum PreviewType {
        Text,
        Audio,
        Video,
        Image,
        Pdf,
        OfficeDoc,
        Other
    };

    PreviewType m_preview_type;
    QString m_extension_name;

    PreviewType getPreviewType();
    QString getExtensionName();
    void sync();

    static std::shared_ptr<PreviewFileType> fromUri(const QString &uri);

private:
    std::shared_ptr<Peony::FileInfo> m_info;
};

#endif // PREVIEWFILETYPE_H
