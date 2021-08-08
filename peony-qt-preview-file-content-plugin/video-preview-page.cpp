#include "video-preview-page.h"
#include <QStyle>
#include <QVideoWidget>

VideoPreviewPage::VideoPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_video_item = new QGraphicsVideoItem;

    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *graphicsView = new QGraphicsView(scene);

    scene->addItem(m_video_item);
    m_player->setVideoOutput(m_video_item);

    m_play_button = new QPushButton(this);
    m_play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    timer = new QTimer();
    timer->setInterval(1000 / 4);
    connect(timer, &QTimer::timeout, this, [=](){
         m_position_slider->setValue(m_player->position());
         qDebug() << m_player->position() << " " << m_player->duration() ;
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
    m_position_slider->setRange(0, 0);

    connect(m_position_slider, &QSlider::sliderMoved,
            this, [=] (int position) {
        m_player->setPosition(position);
    });

    connect(m_player, &QMediaPlayer::durationChanged, this, [=](qint64 duration)
    {
        m_position_slider->setRange(0, duration);
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

    // set layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(graphicsView);
    graphicsView->adjustSize();
    m_layout->addWidget(m_position_slider);
    m_layout->addWidget(m_play_button);
    setLayout(m_layout);
}

void VideoPreviewPage::updateInfo(Peony::FileInfo *info) {
     m_player->setMedia(QUrl(info->uri()));
     m_player->play();
}

void VideoPreviewPage::cancel() {
    m_player->pause();
}
