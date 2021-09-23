#include "previewpage/text.h"

#include <QFile>
#include <QTextStream>

#include <syntaxhighlighter.h>
#include <definition.h>
#include <foldingregion.h>
#include <syntaxhighlighter.h>
#include <theme.h>

TextPreviewPage::TextPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{    
    m_text_edit = new QPlainTextEdit(this);
    m_text_edit->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    m_highlighter = new KSyntaxHighlighting::SyntaxHighlighter(m_text_edit->document());
    m_highlighter->setTheme((palette().color(QPalette::Base).lightness() < 128) ?
                                m_repository.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme) :
                                m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));

    m_save_button = new QPushButton(tr("save"), this);
    connect(m_save_button, &QPushButton::clicked, this, &TextPreviewPage::saveText);
    m_save_button->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));

    base_layout->addWidget(m_text_edit);
    base_layout->addWidget(m_save_button);
}

void TextPreviewPage::cancel() {
    m_text_edit->clear();
    m_file_path.clear();
}

void TextPreviewPage::updateInfo(Peony::FileInfo *info) {
    m_file_path = info->filePath();
    QFile file(m_file_path);
    qDebug() << "TextPreviewPage::updateInfo:" << info->uri();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_text_edit->setPlainText(QString("Failed to open %1").arg(m_file_path));
        return;
    }
    QTextStream in(&file);
    m_text_edit->clear();

    int line_cnt = 0, char_cnt = 0;
    bool write_able = info->canWrite();
    while (!in.atEnd()) {
        QString line = in.readLine(max_line_len);
        if (line.size() == max_line_len)
            write_able = false;
        m_text_edit->appendPlainText(line);
        char_cnt += line.size();
        line_cnt++;
        if (line_cnt > max_line_cnt || char_cnt > max_char_cnt) {
            write_able = false;
            break;
        }
    }
    m_text_edit->setReadOnly(!write_able);
    m_save_button->setEnabled(write_able);
    m_save_button->setVisible(write_able);

    m_text_edit->moveCursor(QTextCursor::Start);

    const auto def = m_repository.definitionForMimeType(info->mimeType());
    m_highlighter->setDefinition(def);
    m_highlighter->rehighlight();
    file.close();
}

void TextPreviewPage::saveText() {
    QFile file(m_file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << QString("Save %1 Failed").arg(m_file_path);
        return;
    }
    QTextStream out(&file);
    out << m_text_edit->toPlainText();
    out.flush();
    file.close();
}
