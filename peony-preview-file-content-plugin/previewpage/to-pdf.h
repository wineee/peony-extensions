#ifndef TOPDFPREVIEWPAGE_H
#define TOPDFPREVIEWPAGE_H


#include <QProcess>

#ifdef USE_OnlyOffice

#include "previewpage/pdf.h"
typedef PdfPreviewPage ToPdfBaseClass;

#else

#include "previewpage/pdf2.h"
typedef Pdf2PreviewPage ToPdfBaseClass;

#endif

class ToPdfPreviewPage : public ToPdfBaseClass
{
public:
    explicit ToPdfPreviewPage(QWidget *parent = nullptr);
    ~ToPdfPreviewPage() = default;

private:
    QProcess *m_proc;
    QString m_pdf_path;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // TOPDFPREVIEWPAGE_H
