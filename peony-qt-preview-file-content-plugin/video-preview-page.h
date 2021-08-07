#ifndef VIDEOPREVIEWPAGE_H
#define VIDEOPREVIEWPAGE_H

#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

#include "base-preview-page.h"
#include "components/slider.h"

class VideoPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit VideoPreviewPage(QWidget *parent = nullptr);
    ~VideoPreviewPage() = default;

private:
    QMediaPlayer *m_player;
    QGraphicsVideoItem *m_video_item;
    QPushButton *m_play_button;
    Slider *m_position_slider;
    QTimer *timer;

public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // VIDEOPREVIEWPAGE_H
