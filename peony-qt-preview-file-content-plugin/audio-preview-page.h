#ifndef AUDIOPREVIEWPAGE_H
#define AUDIOPREVIEWPAGE_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLayout>
#include <QTimer>

#include "base-preview-page.h"
#include "components/slider.h"

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
//    Slider *m_volume_slider;
    QTimer *timer;

    QMediaPlayer *m_player;

    // BasePreviewPage interface
public Q_SLOTS:
    void updateInfo(FileInfo *info) override;
public:
    void cancel() override;
};

#endif // AUDIOPREVIEWPAGE_H
