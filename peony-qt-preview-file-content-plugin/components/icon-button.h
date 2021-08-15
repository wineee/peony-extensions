#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QProxyStyle>

//a clone of "controls/icon-container.h"

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = nullptr);
    ~IconButton();

protected:
    void mouseMoveEvent(QMouseEvent *e) { Q_UNUSED(e) }
    void mousePressEvent(QMouseEvent *e) { Q_UNUSED(e) }
    void paintEvent(QPaintEvent *e);

private:
    QStyle *m_style;
};


class IconButtonStyle : public QProxyStyle
{
    friend class IconButton;
    explicit IconButtonStyle();
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
};

#endif // ICONBUTTON_H
