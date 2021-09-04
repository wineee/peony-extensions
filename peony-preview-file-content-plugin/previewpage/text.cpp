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

    m_save_button = new QPushButton(tr("save"), this);
    connect(m_save_button, &QPushButton::clicked, this, &TextPreviewPage::saveText);
    m_save_button->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));

    m_highlighter = new KSyntaxHighlighting::SyntaxHighlighter(m_text_edit->document());
    m_text_edit->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_highlighter->setTheme((palette().color(QPalette::Base).lightness() < 128) ? m_repository.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme) : m_repository.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));

    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
    m_layout->addWidget(m_text_edit);
    m_layout->addWidget(m_save_button);
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
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
        m_text_edit->appendPlainText(line);
    }
    m_text_edit->moveCursor(QTextCursor::Start);

    const auto defName = "C++"; // only for test
    const auto def = m_repository.definitionForName(defName);
    m_highlighter->setDefinition(def);
    m_highlighter->rehighlight();
    for (const auto t : m_repository.definitions()) {
        qDebug() << t.name();
    }

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
