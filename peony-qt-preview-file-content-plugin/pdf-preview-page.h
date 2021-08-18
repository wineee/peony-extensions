#ifndef PDFPREVIEWPAGE_H
#define PDFPREVIEWPAGE_H

#include <QObject>
#include "base-preview-page.h"

#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfView>
#include <QPdfPageRenderer>
#include <QPdfDocumentRenderOptions>

class PdfPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit PdfPreviewPage(QWidget *parent = nullptr);
    ~PdfPreviewPage() = default;

private Q_SLOTS:
    void onCurrentPageChanged(int page);
    void pageNumberEdited();

private:
    //QPdfPageNavigation *m_page_navigation;
    QPdfDocument *m_document;
    QPdfBookmarkModel *m_bookmark_model;
    QPdfView *m_pdf_view;
    QPdfPageRenderer *m_page_renderer;
    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // PDFPREVIEWPAGE_H
