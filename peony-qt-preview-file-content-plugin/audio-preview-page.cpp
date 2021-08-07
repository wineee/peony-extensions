#include "audio-preview-page.h"
#include <QDebug>
#include <QMediaPlaylist>
#include <QStyle>

AudioPreviewPage::AudioPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_button = new QPushButton(this);
    m_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

    m_player = new QMediaPlayer(this, QMediaPlayer::LowLatency);

    m_progress = new Slider(this);
    m_progress->setMinimum(0);
    connect(m_player, &QMediaPlayer::durationChanged, this, [=]() {
        m_progress->setMaximum(m_player->duration());
    });
    m_progress->setValue(0);

    timer = new QTimer();
    timer->setInterval(1000 / 4);

    connect(m_button, &QPushButton::clicked, this, [=]() {
        switch (m_player->state()) {
        case QMediaPlayer::PlayingState:
            m_player->pause();
            timer->stop();
            break;
        default:
            m_player->play();
            timer->start();
            break;
        }
    });

    connect(m_player, &QMediaPlayer::stateChanged,
            this, [=](QMediaPlayer::State state)
    {
        switch(state) {
        case QMediaPlayer::PlayingState:
            m_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        default:
            m_button->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    });

    connect(timer, &QTimer::timeout, this, [=](){
         m_progress->setValue(m_player->position());
         qDebug() << m_player->position() << " " << m_player->duration() ;
    });
//    connect(m_player, &QMediaPlayer::positionChanged, this, [=]() {
//        m_progress->setValue(m_player->position());
//    });
    connect(m_progress, &Slider::sliderMoved, this, [=]() {
        timer->stop();
    });
    connect(m_progress, &Slider::sliderReleased, this, [=]() {
        m_player->setPosition(m_progress->value());
        timer->start();
    });
    connect(m_progress, &Slider::SliderClicked, this, [=]() {
        m_player->setPosition(m_progress->value());
    });

//    m_volume_slider = new Slider(this);
//    m_layout->addWidget(m_volume_slider);

//    m_player->setVolume(50);
//    m_volume_slider->setValue(50);
//    connect(m_volume_slider, &Slider::MySliderClicked, this, [=]() {
//        m_player->setVolume(m_volume_slider->value());
//    });
//    connect(m_volume_slider, &Slider::sliderMoved, this, [=]() {
//        m_player->setVolume(m_volume_slider->value());
//    });
    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
    m_layout->addWidget(m_button);
    m_layout->addWidget(m_progress);
}

void AudioPreviewPage::updateInfo(FileInfo *info) {
    m_player->setMedia(QUrl(info->uri()));
    m_player->play();
    timer->start();
}

void AudioPreviewPage::cancel() {
    qDebug() << "AudioPreviewPage::cancel";
    m_player->stop();
    timer->stop();
}
