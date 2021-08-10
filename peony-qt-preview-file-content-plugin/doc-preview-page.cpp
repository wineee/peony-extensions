#include "doc-preview-page.h"
#include <QVBoxLayout>
#include <QDebug>

DocPreviewPage::DocPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_web_view = new QWebEngineView;
    m_web_view->setUrl(QUrl("qrc:/index.html"));

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_web_view);
    setLayout(m_layout);
}

void DocPreviewPage::cancel() {
    qDebug() << "DocPreviewPage::cancel: new";
    // qDebug() << m_proc->processId();
    if (m_proc_pid > 0) {
        QProcess::execute(QLatin1String("kill"), QStringList() << QString::number(m_proc_pid));
        // QProcess::execute(QLatin1String("killall"), QStringList()<<"python3");
        m_proc_pid = -1;
    }
}

void DocPreviewPage::updateInfo(Peony::FileInfo *info) {
    qDebug() << "in doc updateInfo";

    QString path = "/", filename, suffixname;
    for (int i = info->filePath().size()-1; i >= 0; i--) {
        if (info->filePath().at(i) == '.' && suffixname.isEmpty())
            suffixname = info->filePath().right(info->filePath().size()-i-1);
        if (info->filePath().at(i) == '/') {
            path = info->filePath().left(i);
            filename = info->filePath().right(info->filePath().size()-i-1);
            break;
        }
    }
    qDebug() << path << " " << filename;

    QProcess m_proc;
    m_proc.setProgram("python3");
    m_proc.setArguments(QStringList() << "-m" << "http.server"
                       << "-d" << path
                       << "-b" << "localhost" << "9124");

    m_proc.startDetached(&m_proc_pid);
    /**
     * @brief update(documentType, fileType, fileName)
     *  word : docx doc odt txt
     *  cell : xlsx xls ods csv
     *  slide : pptx ppt odp
     */
    QStringList wordTypes, cellTypes, slideTypes;
    wordTypes << "docx" << "doc" << "odt" << "txt";
    cellTypes << "xlsx" << "xls" << "ods" << "csv";
    slideTypes << "pptx" << "ppt" << "odp";

    QString method;
    if (wordTypes.contains(suffixname))
        method = QString("update(\"%1\",\"%2\",\"%3\")").arg("word").arg(suffixname).arg(filename);
    else if (cellTypes.contains(suffixname))
        method = QString("update(\"%1\",\"%2\",\"%3\")").arg("cell").arg(suffixname).arg(filename);
    else if (slideTypes.contains(suffixname))
        method = QString("update(\"%1\",\"%2\",\"%3\")").arg("slide").arg(suffixname).arg(filename);
    else
        method = QString("show(\"%1\")").arg("Cann not preview this file.");
    m_web_view->reload();
    connect(m_web_view, &QWebEngineView::loadFinished, [this, method]() {
        m_web_view->page()->runJavaScript(method);
    });
    qDebug() << "out doc updateInfo";
}
