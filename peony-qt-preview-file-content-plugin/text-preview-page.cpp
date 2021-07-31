#include "text-preview-page.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

TextPreviewPage::TextPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_layout = new QHBoxLayout(this);
    setLayout(m_layout);
    m_text_edit = new QPlainTextEdit(this);
    m_layout->addWidget(m_text_edit);
}

void TextPreviewPage::cancel() {
    m_text_edit->clear();
}

void TextPreviewPage::updateInfo(FileInfo *info) {
    QFile file(info->filePath());
    qDebug() << "TextPreviewPage::updateInfo:" << info->uri();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    m_text_edit->clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
        m_text_edit->appendPlainText(line);
    }
}
