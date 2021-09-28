#ifndef IMAGEPREVIEWPAGE_H
#define IMAGEPREVIEWPAGE_H

#include "previewpage/base.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPushButton>

class ImagePreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit ImagePreviewPage(QWidget *parent = nullptr);
    ~ImagePreviewPage();

private:
    QGraphicsScene  *m_image_scene;
    QGraphicsView *m_image_view;
    QGraphicsPixmapItem *m_image_item;

    qreal m_scale;
    qreal m_base_scale;
    bool m_is_moveing;
    QPoint m_last_point;

    QPushButton *m_horizontal_flip_button;
    QPushButton *m_vertical_flip_button;
    QPushButton *m_reduce_button;
    QPushButton *m_enlarge_button;
    QPushButton *m_rotate_button;
    QPushButton *m_adaptive_button;

    QFrame *m_tool_bar;
    QHBoxLayout *m_tool_layout;

    void initControlQss();

    void doHorizontalFlip();
    void doVerticalFlip();
    void doRotate();
    void doReduce();
    void doEnlarge();
    void doAdaptive();

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // IMAGEPREVIEWPAGE_H
