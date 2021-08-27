#include "content-preview-page.h"

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

ContentPreviewPage::ContentPreviewPage(QWidget *parent) : QStackedWidget(parent)
{
    qDebug() << "Init ContentPreviewPage";

    setContentsMargins(10, 0, 10, 0);
    auto label = new QLabel(tr("Select the file you want to preview..."), this);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    m_empty_tab_widget = label;

    auto previewPage = new OtherPreviewPage(this);
    m_other_preview_widget = previewPage;

    m_preview_widget[0] = new AudioPreviewPage(this);
    m_preview_widget[1] = new TextPreviewPage(this);
    m_preview_widget[2] = new PdfPreviewPage(this);
    m_preview_widget[3] = new VideoPreviewPage(this);
    m_preview_widget[4] = new ImagePreviewPage(this);
    m_preview_widget[5] = new DocPreviewPage(this);
    m_preview_widget[6] = new HtmlPreviewPage(this);

    addWidget(m_other_preview_widget);
    addWidget(m_empty_tab_widget);
    for (int cas = 0; cas < 7; ++cas) {
        addWidget(m_preview_widget[cas]);
    }
    setCurrentWidget(m_empty_tab_widget);
    m_preview_cas = -1;
}

ContentPreviewPage::~ContentPreviewPage()
{
    cancel();
}


void ContentPreviewPage::prepare(const QString &uri, PreviewType type) {
    qDebug() << "prepare: " << uri << " " << type;
    m_current_uri = uri;
    m_current_type = type;

    m_info = Peony::FileInfo::fromUri(uri);
    m_support = uri.contains("file:///");

    m_watcher = std::make_shared<Peony::FileWatcher>(uri);
    connect(m_watcher.get(), &Peony::FileWatcher::locationChanged, [=](const QString &, const QString &newUri) {
        this->prepare(newUri);
        this->startPreview();
    });
    m_watcher->startMonitor();
}

void ContentPreviewPage::prepare(const QString &uri) {
    prepare(uri, PreviewType::Other);
}

void ContentPreviewPage::startPreview() {
    qDebug() << "startPreview: " << m_current_uri<< " type:" << m_current_type;
    if (m_info->displayName().isEmpty()) {
        Peony::FileInfoJob j(m_info->uri());
        j.querySync();
    }

    qDebug() << m_info->fileType();

    if (m_support) {
        do {
            if (m_info->fileType().contains("audio")) {
                auto previewPage = qobject_cast<AudioPreviewPage*>(m_preview_widget[0]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                m_preview_cas = 0;
                break;
            }
            if (m_info->fileType().contains("text")) {
                auto previewPage = qobject_cast<TextPreviewPage*>(m_preview_widget[1]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                m_preview_cas = 1;
                break;
            }
            if (m_current_uri.contains(".pdf")) {
                auto previewPage = qobject_cast<PdfPreviewPage*>(m_preview_widget[2]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                m_preview_cas = 2;
                break;
            }
            if (m_current_uri.contains(".mp4")) {
                auto previewPage = qobject_cast<VideoPreviewPage*>(m_preview_widget[3]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                m_preview_cas = 3;
                break;
            }
            if (m_current_uri.contains(".png") || m_current_uri.contains(".jpg") || m_current_uri.contains(".jpeg")) {
                auto previewPage = qobject_cast<ImagePreviewPage*>(m_preview_widget[4]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                m_preview_cas = 4;
                break;
            }
            if (m_current_uri.contains(".doc")) {
                auto previewPage = qobject_cast<DocPreviewPage*>(m_preview_widget[5]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                m_preview_cas = 5;
                break;
            }
            if (m_current_uri.contains(".html")) {
                auto previewPage = qobject_cast<HtmlPreviewPage*>(m_preview_widget[6]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                m_preview_cas = 6;
                break;
            }
            auto previewPage = qobject_cast<OtherPreviewPage*>(m_other_preview_widget);
            previewPage->updateInfo(m_info.get());
            setCurrentWidget(previewPage);
            m_preview_cas = -1;
            break;
        } while (1);
    } else {
        m_preview_cas = -1;
        QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
        label->setText(tr("Cann not preview this file."));
    }
}

void ContentPreviewPage::cancel() {
    qDebug() << "in cancel ";
    for (int i = 0; i < 6; i++)
        m_preview_widget[i]->cancel();

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
