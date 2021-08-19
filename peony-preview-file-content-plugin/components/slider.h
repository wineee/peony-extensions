#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>
#include <QMouseEvent>

class Slider : public QSlider
{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = nullptr);
    ~Slider() = default;
protected:
    void mousePressEvent(QMouseEvent *ev) override;
Q_SIGNALS:
    void SliderClicked();
};

#endif // SLIDER_H
