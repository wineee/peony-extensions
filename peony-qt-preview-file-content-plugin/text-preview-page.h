#ifndef TEXTPREVIEWPAGE_H
#define TEXTPREVIEWPAGE_H

#include "base-preview-page.h"

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QLayout>

class TextPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit TextPreviewPage(QWidget *parent = nullptr);
    ~TextPreviewPage() = default;

    void cancel() override;

private:
    QPlainTextEdit *m_text_edit;

public Q_SLOTS:
    void updateInfo(FileInfo *info) override;
};

#endif // TEXTPREVIEWPAGE_H
