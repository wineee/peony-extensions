#include "audio-preview-page.h"
#include <QDebug>

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
    m_layout = new QGridLayout(this);
    setLayout(m_layout);

    m_layout->addWidget(m_button);

    m_player = new QMediaPlayer(this, QMediaPlayer::LowLatency);

    m_progress = new Slider(this);
    m_layout->addWidget(m_progress);

    m_progress->setMinimum(0);
    m_progress->setMaximum(1000);
    m_progress->setValue(0);

    connect(m_button, &QPushButton::clicked, this, [=]() {
        switch (m_player->state()) {
        case QMediaPlayer::PlayingState:
            m_player->pause();
            break;
        default:
            m_player->play();
            break;
        }
    });

    timer = new QTimer();
    timer->setInterval(1000 / 4);

    connect(timer, &QTimer::timeout, this, [=](){
         m_progress->setValue(1000 * m_player->position() / m_player->duration());
         qDebug() << m_player->position() << " " << m_player->duration() ;
    });
    connect(m_progress, &Slider::sliderMoved, this, [=]() {
        timer->stop();
        m_player->setPosition(m_progress->value() * m_player->duration() / 1000);
    });
    connect(m_progress, &Slider::sliderReleased, this, [=]() {
        timer->start();
    });
    connect(m_progress, &Slider::MySliderClicked, this, [=]() {
        m_player->setPosition(m_progress->value() * m_player->duration() / 1000);
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
