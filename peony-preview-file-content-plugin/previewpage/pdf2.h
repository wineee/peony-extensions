#ifndef PDF2PREVIEWPAGE_H
#define PDF2PREVIEWPAGE_H

#include "previewpage/base.h"
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QProcess>
#include "QPdfWidget"

class Pdf2PreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit Pdf2PreviewPage(QWidget *parent = nullptr);
    ~Pdf2PreviewPage() = default;

//    QWebEngineView *m_web_view;
//    QWebChannel *m_web_channel;
//    QWebEnginePage *m_web_page;

    QPdfWidget *m_pdf_widget;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // PDF2PREVIEWPAGE_H
