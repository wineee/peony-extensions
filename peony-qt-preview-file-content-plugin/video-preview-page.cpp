#include "video-preview-page.h"
#include <QStyle>
#include <QVideoWidget>

VideoPreviewPage::VideoPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_video_item = new QGraphicsVideoItem;

    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *graphicsView = new QGraphicsView(scene);

    scene->addItem(m_video_item);
    //m_video_widget = new QVideoWidget(this);
    m_player->setVideoOutput(m_video_item);

    m_play_button = new QPushButton(this);
    m_play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

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

    m_position_slider = new QSlider(Qt::Horizontal);
    m_position_slider->setRange(0, 0);

    connect(m_position_slider, &QSlider::sliderMoved,
            this, [=] (int position) {
        m_player->setPosition(position);
    });

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(graphicsView);
    m_layout->addWidget(m_position_slider);
    m_layout->addWidget(m_play_button);
    setLayout(m_layout);

    connect(m_player, &QMediaPlayer::stateChanged,
            this, [=](QMediaPlayer::State state)
    {
        switch(state) {
        case QMediaPlayer::PlayingState:
            m_play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        default:
            m_play_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    });
    connect(m_player, &QMediaPlayer::positionChanged, this, [=](qint64 position)
    {
        m_position_slider->setValue(position);
    });
    connect(m_player, &QMediaPlayer::durationChanged, this, [=](qint64 duration)
    {
        m_position_slider->setRange(0, duration);
    });
}

void VideoPreviewPage::updateInfo(Peony::FileInfo *info) {
     m_player->setMedia(QUrl(info->uri()));
     m_player->play();
}

void VideoPreviewPage::cancel() {
    m_player->pause();
}
