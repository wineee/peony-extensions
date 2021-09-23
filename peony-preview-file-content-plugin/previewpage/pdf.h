#ifndef PDFPREVIEWPAGE_H
#define PDFPREVIEWPAGE_H

#include "previewpage/base.h"

#include <QPdfBookmarkModel>
#include <QPdfDocument>
#include <QPdfView>
//#include <QPdfPageRenderer>
//#include <QtPdf>

/*
class QPdfWidget : public QPdfView {
    Q_OBJECT
public:
    explicit QPdfWidget(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};
*/

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
    QPdfDocument *m_document;
    QPdfBookmarkModel *m_bookmark_model;
    QPdfView *m_pdf_view;
    //QPdfPageRenderer *m_page_renderer;
    //QPdfPageNavigation *m_page_navigation;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
    void updateInfo(QString path);
};

#endif // PDFPREVIEWPAGE_H
