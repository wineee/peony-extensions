#include "previewpage/audio.h"

#include <QDebug>
#include <QMediaPlaylist>
#include <QStyle>

AudioPreviewPage::AudioPreviewPage(QWidget *parent) : BasePreviewPage(parent)
{
    m_button = new QPushButton(this);
    m_button->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    //m_button->setFixedSize(200, 100);
    //m_button->setIconSize(QSize(200, 100));

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
/*
    m_volume_slider = new Slider(this);
    m_layout->addWidget(m_volume_slider);

    m_player->setVolume(50);
    m_volume_slider->setValue(50);
    connect(m_volume_slider, &Slider::MySliderClicked, this, [=]() {
        m_player->setVolume(m_volume_slider->value());
    });
    connect(m_volume_slider, &Slider::sliderMoved, this, [=]() {
        m_player->setVolume(m_volume_slider->value());
    });
*/
    m_icon = new IconButton(this);
    m_icon->setIconSize(QSize(96, 96));
    connect(m_player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &AudioPreviewPage::updateMeta);

    m_form = new QFormLayout;
    m_title_label = new QLabel(this);
    m_title_label->setWordWrap(true);
    m_form->addRow(tr("Title:"), m_title_label);
    m_author_label = new QLabel(this);
    m_form->addRow(tr("Author:"), m_author_label);

    m_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    m_form->setFormAlignment(Qt::AlignHCenter);
    m_form->setLabelAlignment(Qt::AlignRight);

    m_layout = new QVBoxLayout(this);
    setLayout(m_layout);
    m_layout->addWidget(m_icon);
    QWidget *form = new QWidget(this);
    form->setLayout(m_form);
    form->setMaximumHeight(100);
    m_layout->addWidget(form);
    m_layout->addWidget(m_progress);
    m_layout->addWidget(m_button);
}

void AudioPreviewPage::updateInfo(Peony::FileInfo *info) {
    m_player->setMedia(QUrl(info->uri()));
    m_player->play();
    timer->start();
    m_base_icon = QIcon::fromTheme(info->iconName(), QIcon::fromTheme("text-x-generic"));
}

void AudioPreviewPage::cancel() {
    qDebug() << "AudioPreviewPage::cancel";
    m_player->stop();
    timer->stop();
}

void AudioPreviewPage::updateMeta() {
    QVariant cover_val = m_player->metaData("CoverArtImage");
    const QIcon &icon = QIcon(QPixmap::fromImage(cover_val.value<QImage>()));
    m_icon->setIcon(icon.isNull() ? m_base_icon : icon);

    QVariant title = m_player->metaData("Title");
    if (title.isValid())
        m_title_label->setText(title.toString());

    QVariant autor = m_player->metaData("ContributingArtist");
    if (autor.isValid())
        m_author_label->setText(autor.toString());
    // qDebug() << m_player->availableMetaData() << "\n";
}


void AudioPreviewPage::resizeEvent(QResizeEvent* event) {
    int width = event->size().width() - 50;
    width = qMax(width, 96);
    width = qMin(width, 256);
    m_icon->setIconSize(QSize(width, width * 2/3));
}
