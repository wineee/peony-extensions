#include "audio-preview-page.h"
#include <QDebug>
#include <QMediaPlaylist>

Slider::Slider(QWidget *parent) : QSlider(parent)
{
    setOrientation(Qt::Horizontal);
}

void Slider::mousePressEvent(QMouseEvent *ev) {
    QSlider::mousePressEvent(ev);
    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());
    Q_EMIT MySliderClicked();
}

AudioPreviewPage::AudioPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_button = new QPushButton(this);
    m_button->setText("停止播放");
    m_layout = new QGridLayout(this);
    setLayout(m_layout);
    m_layout->addWidget(m_button);

    m_player = new QMediaPlayer(this, QMediaPlayer::LowLatency);

    m_progress = new Slider(this);
    m_layout->addWidget(m_progress);

    m_progress->setMinimum(0);
    connect(m_player, &QMediaPlayer::durationChanged, this, [=]() {
        m_progress->setMaximum(m_player->duration());
    });
    m_progress->setValue(0);

    connect(m_button, &QPushButton::clicked, this, [=]() {
        switch (m_player->state()) {
        case QMediaPlayer::PlayingState:
            m_player->pause();
            m_button->setText("继续播放");
            break;
        default:
            m_player->play();
            m_button->setText("停止播放");
            break;
        }
    });

    timer = new QTimer();
    timer->setInterval(1000 / 4);

    connect(timer, &QTimer::timeout, this, [=](){
         m_progress->setValue(m_player->position());
         if (m_player->position() == m_player->duration())
             m_button->setText("继续播放");
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
    connect(m_progress, &Slider::MySliderClicked, this, [=]() {
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
