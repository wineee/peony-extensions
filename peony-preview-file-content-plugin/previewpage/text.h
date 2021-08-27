#ifndef TEXTPREVIEWPAGE_H
#define TEXTPREVIEWPAGE_H

#include "previewpage/base.h"

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QPushButton>

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

    void saveText();

//   TextPreviewPage* TextPreviewPage::getInstance() {
//        if (!globalInstance) {
//            globalInstance = new TextPreviewPage;
//        }
//        return globalInstance;
//    }
    // BasePreviewPage interface
public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
public:
    void cancel() override;

};

#endif // TEXTPREVIEWPAGE_H
