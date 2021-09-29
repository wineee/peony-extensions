#ifndef TEXTPREVIEWPAGE_H
#define TEXTPREVIEWPAGE_H

#include "previewpage/base.h"

#include <QPlainTextEdit>
#include <QPushButton>

#ifdef USE_KSyntaxHighlighting
#include <repository.h>
namespace KSyntaxHighlighting
{
class SyntaxHighlighter;
class Repository;
}
#endif

class TextPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit TextPreviewPage(QWidget *parent = nullptr);
    ~TextPreviewPage() = default;

private:
    static const int max_line_cnt = 1000;
    static const int max_line_len = 1000;
    static const int max_char_cnt = 10000;

    QPlainTextEdit *m_text_edit;
    QString m_file_path;
    QPushButton *m_save_button;

#ifdef USE_KSyntaxHighlighting
    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;
#endif

    void saveText();

    // BasePreviewPage interface
public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
public:
    void cancel() override;

};

#endif // TEXTPREVIEWPAGE_H
