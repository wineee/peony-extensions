#ifndef IMAGEPREVIEWPAGE_H
#define IMAGEPREVIEWPAGE_H

#include "base-preview-page.h"

#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPushButton>

class ImagePreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit ImagePreviewPage(QWidget *parent = nullptr);
    ~ImagePreviewPage() = default;

private:
    QImage image;
    QGraphicsScene  *m_image_scene;
    QGraphicsView *m_image_view;
    QGraphicsPixmapItem *m_image_item;

    QPushButton *m_horizontal_flip_button;
    QPushButton *m_vertical_flip_button;

    void doHorizontalFlip();
    void doVerticalFlip();

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // IMAGEPREVIEWPAGE_H
