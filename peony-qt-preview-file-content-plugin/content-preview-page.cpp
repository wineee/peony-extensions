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
    previewPage->installEventFilter(this);
    m_other_preview_widget = previewPage;

    m_preview_widget[0] = new AudioPreviewPage(this);
    m_preview_widget[1] = new TextPreviewPage(this);
    m_preview_widget[2] = new PdfPreviewPage(this);
    addWidget(m_other_preview_widget);
    addWidget(m_empty_tab_widget);
    for (int cas = 0; cas < 3; ++cas) {
        addWidget(m_preview_widget[cas]);
    }
    setCurrentWidget(m_empty_tab_widget);
}

ContentPreviewPage::~ContentPreviewPage()
{
    cancel();
}


void ContentPreviewPage::prepare(const QString &uri, PreviewType type) {
    qDebug() << "prepare: " << uri << " " << type;
    m_current_uri = uri;
    m_current_type = type;

    m_info = FileInfo::fromUri(uri);
    m_support = uri.contains("file:///");

    m_watcher = std::make_shared<FileWatcher>(uri);
    connect(m_watcher.get(), &FileWatcher::locationChanged, [=](const QString &, const QString &newUri) {
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
        FileInfoJob j(m_info->uri());
        j.querySync();
    }

    qDebug() << m_info->fileType();

    if (m_support) {
        do {
            if (m_info->fileType().contains("audio")) {
                auto previewPage = qobject_cast<AudioPreviewPage*>(m_preview_widget[0]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                break;
            }
            if (m_info->fileType().contains("text")) {
                auto previewPage = qobject_cast<TextPreviewPage*>(m_preview_widget[1]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                break;
            }
            if (m_current_uri.contains(".pdf")) {
                auto previewPage = qobject_cast<PdfPreviewPage*>(m_preview_widget[2]);
                previewPage->updateInfo(m_info.get());
                setCurrentWidget(previewPage);
                break;
            }
            auto previewPage = qobject_cast<OtherPreviewPage*>(m_other_preview_widget);
            previewPage->updateInfo(m_info.get());
            setCurrentWidget(previewPage);
            break;
        } while (1);
    } else {
        QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
        label->setText(tr("Cann not preview this file."));
    }
}

void ContentPreviewPage::cancel() {
    qDebug() << "in cancel ";

    m_preview_widget[0]->cancel();

    setCurrentWidget(m_empty_tab_widget);
    QLabel *label = qobject_cast<QLabel*>(m_empty_tab_widget);
    label->setText(tr("Select the file you want to preview..."));
    qDebug() << "out cancel";
}

bool ContentPreviewPage::eventFilter(QObject *obj, QEvent *ev) {
    if (obj == m_other_preview_widget) {
        if (ev->type() == QEvent::Resize) {
            auto e = static_cast<QResizeEvent*>(ev);
            auto page = qobject_cast<OtherPreviewPage*>(m_other_preview_widget);
            int width = e->size().width() - 50;
            width = qMax(width, 96);
            width = qMin(width, 256);
            page->resizeIcon(QSize(width, width * 2/3));
        }
    }
    return QWidget::eventFilter(obj, ev);
}

void ContentPreviewPage::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(this->rect(), this->palette().base());
    QWidget::paintEvent(e);
}
