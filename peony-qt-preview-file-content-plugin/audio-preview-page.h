#ifndef AUDIOPREVIEWPAGE_H
#define AUDIOPREVIEWPAGE_H

#include <QWidget>
#include <QMediaPlayer>
#include <QDir>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QSlider>
#include <QMouseEvent>

#include "base-preview-page.h"

class Slider : public QSlider
{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = nullptr);
    ~Slider() = default;
protected:
    void mousePressEvent(QMouseEvent *ev);
Q_SIGNALS:
    void MySliderClicked();
};


class AudioPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit AudioPreviewPage(QWidget *parent = nullptr);
    ~AudioPreviewPage() = default;
private:
    QPushButton *m_button;
    QPushButton *volume_button;
    QLayout *m_layout;
    Slider *m_progress;
    Slider *m_volume_slider;
    QTimer *timer;

    bool isPlay = false;
    //QString MusicPath;

    QMediaPlayer *m_player;

public Q_SLOTS:
    void updateInfo(FileInfo *info) override;
public:
    void cancel() override;
};

#endif // AUDIOPREVIEWPAGE_H
