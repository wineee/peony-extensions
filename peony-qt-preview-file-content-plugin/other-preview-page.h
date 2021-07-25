#ifndef OTHERPREVIEWPAGE_H
#define OTHERPREVIEWPAGE_H

#include <QLabel>
#include <QStackedWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QIcon>
#include <QWidget>

#include <QFile>
#include <QFileInfo>
#include <QUrl>

#include "base-preview-page.h"

#include "peony-qt/file-info.h"
#include "peony-qt/controls/icon-container.h"
#include "peony-qt/thumbnail-manager.h"
#include "peony-qt/file-info-job.h"

using Peony::FileInfoJob;
using Peony::FileInfo;
using Peony::ThumbnailManager;

class OtherPreviewPage : public BasePreviewPage
{
    friend class ContentPreviewPage;
    Q_OBJECT
private:
    explicit OtherPreviewPage(QWidget *parent = nullptr);
    ~OtherPreviewPage();

private Q_SLOTS:
    void updateInfo(FileInfo *info);
    void resizeIcon(QSize size);

private:
    QGridLayout *m_layout;
    //Peony::IconContainer *m_icon;
    QFormLayout *m_form;
    QLabel *m_display_name_label;
    QLabel *m_type_label;
    QLabel *m_time_modified_label;
    QLabel *m_time_access_label;

    //image
    QLabel *m_image_size;
    QLabel *m_image_format;
};

#endif // OTHERPREVIEWPAGE_H
