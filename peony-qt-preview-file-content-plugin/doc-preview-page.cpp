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
    //    qDebug() << m_proc->processId() << " eddd";
    if (m_proc_pid > 0) {
        QProcess::execute(QLatin1String("kill"), QStringList() << QString::number(m_proc_pid));
        // QProcess::execute(QLatin1String("killall"), QStringList()<<"python3");
        m_proc_pid = -1;
    }
}

void DocPreviewPage::updateInfo(Peony::FileInfo *info) {
    qDebug() << "in doc updateInfo";

    QProcess m_proc;
    m_proc.setProgram("python3");
    m_proc.setArguments(QStringList() << "-m" << "http.server"
                       //<< "-d" << "\"/home/rewine\""
                       << "-b" << "localhost" << "9124");

    m_proc.startDetached(&m_proc_pid);

    qDebug() << "out doc updateInfo";
}
