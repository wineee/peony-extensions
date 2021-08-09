#ifndef DOCPREVIEWPAGE_H
#define DOCPREVIEWPAGE_H

#include "base-preview-page.h"
#include <QWebChannel>
#include <QWebEngineView>
#include <QProcess>

class DocPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit DocPreviewPage(QWidget *parent = nullptr);
    ~DocPreviewPage() = default;

private:
    QWebEngineView *m_web_view = nullptr;
    qint64 m_proc_pid = -1;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // DOCPREVIEWPAGE_H
