#ifndef HTMLPREVIEWPAGE_H
#define HTMLPREVIEWPAGE_H

#include "base-preview-page.h"

#include <QWebChannel>
#include <QWebEngineView>
#include <QWebEnginePage>

class HtmlPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit HtmlPreviewPage(QWidget *parent = nullptr);
    ~HtmlPreviewPage() = default;

private:
    QWebEngineView *m_web_view;
    QWebChannel *m_web_channel;
    QWebEnginePage *m_web_page;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // HTMLPREVIEWPAGE_H
