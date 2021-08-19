#include "slider.h"

Slider::Slider(QWidget *parent) : QSlider(parent) {
    setOrientation(Qt::Horizontal);
}

void Slider::mousePressEvent(QMouseEvent *ev) {
    QSlider::mousePressEvent(ev);
    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());
    Q_EMIT SliderClicked();
}
