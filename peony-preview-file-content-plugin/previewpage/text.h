#ifndef TEXTPREVIEWPAGE_H
#define TEXTPREVIEWPAGE_H

#include "previewpage/base.h"

#include <repository.h>
#include <QPlainTextEdit>
#include <QPushButton>

namespace KSyntaxHighlighting
{
class SyntaxHighlighter;
class Repository;
}

class TextPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit TextPreviewPage(QWidget *parent = nullptr);
    ~TextPreviewPage() = default;

private:
    QPlainTextEdit *m_text_edit;
    QString m_file_path;
    QPushButton *m_save_button;

    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;

    void saveText();

    // BasePreviewPage interface
public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
public:
    void cancel() override;

};

#endif // TEXTPREVIEWPAGE_H
