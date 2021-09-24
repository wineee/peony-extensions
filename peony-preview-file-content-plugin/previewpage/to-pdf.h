#ifndef TOPDFPREVIEWPAGE_H
#define TOPDFPREVIEWPAGE_H

#include "previewpage/pdf2.h"

#include <QProcess>

class ToPdfPreviewPage : public Pdf2PreviewPage
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
