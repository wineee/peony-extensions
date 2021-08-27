#include "previewpage/video.h"

#include <QStyle>
#include <QSpacerItem>

VideoPreviewPage::VideoPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_video_item = new QGraphicsVideoItem;
    m_video_scene = new QGraphicsScene;
    m_video_view = new QGraphicsView(m_video_scene);
    m_video_view->setDragMode(QGraphicsView::NoDrag);
    m_video_view->setStyleSheet("padding:0px;border:0px");

    m_video_scene->addItem(m_video_item);
    m_player->setVideoOutput(m_video_item);

    m_play_button = new QPushButton(this);
    m_play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    timer = new QTimer();
    timer->setInterval(1000 / 4);
    connect(timer, &QTimer::timeout, this, [=](){
         m_position_slider->setValue(m_player->position());
         //qDebug() << m_player->position() << " " << m_player->duration() ;
    });

    connect(m_play_button, &QPushButton::clicked, this, [=]() {
        switch (m_player->state()) {
        case QMediaPlayer::PlayingState:
            m_player->pause();
            break;
        default:
            m_player->play();
            break;
        }
    });

    connect(m_player, &QMediaPlayer::stateChanged,
            this, [=](QMediaPlayer::State state)
    {
        switch(state) {
        case QMediaPlayer::PlayingState:
            m_play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            timer->start();
            break;
        default:
            m_play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            timer->stop();
            break;
        }
    });

    // position slider
    m_position_slider = new Slider(this);
    connect(m_player, &QMediaPlayer::durationChanged, this, [=](qint64 duration)
    {
        m_position_slider->setRange(0, duration);
    });

    connect(m_position_slider, &QSlider::sliderMoved,
            this, [=] (int position) {
        m_player->setPosition(position);
    });

    connect(m_position_slider, &Slider::sliderMoved, this, [=]() {
        timer->stop();
    });
    connect(m_position_slider, &Slider::sliderReleased, this, [=]() {
        m_player->setPosition(m_position_slider->value());
        timer->start();
    });
    connect(m_position_slider, &Slider::SliderClicked, this, [=]() {
        m_player->setPosition(m_position_slider->value());
    });

    connect(m_video_item, &QGraphicsVideoItem::nativeSizeChanged, this, [this]() {
        qDebug() << "nativeSizeChanged:" << m_video_item->boundingRect().isValid();
        QResizeEvent *event = new QResizeEvent(size(), size());
        Q_EMIT resizeEvent(event);
    });
    // set layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_video_view, 30);
    //m_video_view->setSizePolicy(QSizePolicy::Expanding ,QSizePolicy::Expanding);
    //m_video_view->adjustSize();
    layout->addStretch(1);
    layout->addWidget(m_position_slider);
    //layout->addSpacing(20);
    layout->addStretch(1);
    layout->addWidget(m_play_button);
    layout->addStretch(1);
    setLayout(layout);
    m_layout = layout;
}

VideoPreviewPage::~VideoPreviewPage() {
    m_video_scene->deleteLater();
}

void VideoPreviewPage::updateInfo(Peony::FileInfo *info) {
     m_player->setMedia(QUrl(info->uri()));
     m_player->play();
     qDebug() << m_video_item->boundingRect();
}

void VideoPreviewPage::cancel() {
    m_player->pause();
}

void VideoPreviewPage::resizeEvent(QResizeEvent *event) {
    qDebug() << "     VideoPreviewPage::resizeEvent" << event->size() << " "
             << m_video_item->boundingRect() << " " << m_video_item->nativeSize();

    if (m_video_scene->sceneRect().isValid()) {
        qDebug() << m_video_scene->sceneRect() << " " << m_video_item->boundingRect();
        m_video_view->resetTransform();
        int height = m_video_scene->sceneRect().height();
        int width = m_video_scene->sceneRect().width();
        int max_height = m_video_view->height() - 5;
        int max_width = m_video_view->width() - 5;
        double val =  qMin(1.0 * max_width / width, 1.0 * max_height / height);
        m_video_view->scale(val, val);
        qDebug() << "Resize:" << val;
    }
}
