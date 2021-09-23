#ifndef PDF2PREVIEWPAGE_H
#define PDF2PREVIEWPAGE_H

#include "previewpage/base.h"
#include "QPdfWidget"

class Pdf2PreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit Pdf2PreviewPage(QWidget *parent = nullptr);
    ~Pdf2PreviewPage() = default;

private:
    QPdfWidget *m_pdf_widget;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
    void updateInfo(QString path);
};

#endif // PDF2PREVIEWPAGE_H
