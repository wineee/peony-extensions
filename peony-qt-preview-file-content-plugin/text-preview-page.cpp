#include "text-preview-page.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

TextPreviewPage::TextPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{    
    m_text_edit = new QPlainTextEdit(this);
    m_text_edit->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    m_save_button = new QPushButton(tr("save"), this);
    connect(m_save_button, &QPushButton::clicked, this, &TextPreviewPage::saveText);
    m_save_button->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));

    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
    m_layout->addWidget(m_text_edit);
    m_layout->addWidget(m_save_button);
}

void TextPreviewPage::cancel() {
    m_text_edit->clear();
    m_file_path.clear();
}

void TextPreviewPage::updateInfo(FileInfo *info) {
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
