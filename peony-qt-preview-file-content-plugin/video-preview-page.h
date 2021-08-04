#ifndef VIDEOPREVIEWPAGE_H
#define VIDEOPREVIEWPAGE_H

#include "base-preview-page.h"
#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

#include <QVideoWidget>

class VideoPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit VideoPreviewPage(QWidget *parent = nullptr);
    ~VideoPreviewPage() = default;

private:
    QMediaPlayer *m_player = nullptr;
    QGraphicsVideoItem *m_video_item = nullptr;
    QPushButton *m_play_button = nullptr;
    QSlider *m_position_slider = nullptr;
    QLayout *m_layout;

public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
};

#endif // VIDEOPREVIEWPAGE_H
