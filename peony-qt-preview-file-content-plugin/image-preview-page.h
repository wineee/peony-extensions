#ifndef IMAGEPREVIEWPAGE_H
#define IMAGEPREVIEWPAGE_H

#include <QObject>
#include "base-preview-page.h"

#include <QImage>
#include <QLabel>
#include <QScrollArea>

class ImagePreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit ImagePreviewPage(QWidget *parent = nullptr);
    ~ImagePreviewPage() = default;

private:
    QImage image;
    QLabel *m_image_label;
    QScrollArea *m_scroll_area;
    QLayout *m_layout;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // IMAGEPREVIEWPAGE_H
