#ifndef TOPDFPREVIEWPAGE_H
#define TOPDFPREVIEWPAGE_H

#include "previewpage/pdf.h"

class ToPdfPreviewPage : public PdfPreviewPage
{
public:
    explicit ToPdfPreviewPage(QWidget *parent = nullptr);
    ~ToPdfPreviewPage() = default;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // TOPDFPREVIEWPAGE_H
