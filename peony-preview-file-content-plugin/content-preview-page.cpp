#include "content-preview-page.h"
#include "preview-page-manger.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QUrl>
#include <QMimeDatabase>
#include <QLocale>
#include <QResizeEvent>
#include <QDebug>

#include <file-watcher.h>


ContentPreviewPage::ContentPreviewPage(QWidget *parent) : QStackedWidget(parent)
{
    qDebug() << "Init ContentPreviewPage";

    setContentsMargins(10, 0, 10, 0);
    auto label = new QLabel(tr("Select the file you want to preview..."), this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    m_empty_tab_widget = label;
    addWidget(m_empty_tab_widget);
    setCurrentWidget(m_empty_tab_widget);

    m_page_manger = new PreviewPageManger(this);
}

ContentPreviewPage::~ContentPreviewPage()
{
    cancel();
    delete m_page_manger;
}


void ContentPreviewPage::prepare(const QString &uri) {
    qDebug() << "prepare: " << uri;
    m_current_uri = uri;

    m_file_info = PreviewFileType::fromUri(uri);
    m_support = uri.contains("file:///");

    m_watcher = std::make_shared<Peony::FileWatcher>(uri);
    connect(m_watcher.get(), &Peony::FileWatcher::locationChanged, [=](const QString &, const QString &newUri) {
        this->prepare(newUri);
        this->startPreview();
    });
    m_watcher->startMonitor();
}

void ContentPreviewPage::startPreview() {
    qDebug() << "startPreview: " << m_current_uri;
    m_file_info->sync();

    if (m_support) {
        m_page_manger->startPreview(m_file_info.get());
    } else {
        QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
        label->setText(tr("Cann not preview this file."));
    }
}

void ContentPreviewPage::cancel() {
    qDebug() << "in cancel ";
    m_page_manger->cancel();

    setCurrentWidget(m_empty_tab_widget);
    QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
    label->setText(tr("Select the file you want to preview..."));
    qDebug() << "out cancel";
}

void ContentPreviewPage::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(this->rect(), this->palette().base());
    QWidget::paintEvent(e);
}
