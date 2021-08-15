#include "icon-button.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOptionButton>
#include <QDebug>

IconButton::IconButton(QWidget *parent) : QPushButton(parent)
{
    setEnabled(true);
    setCheckable(false);
    setDefault(true);
    setFlat(true);

    m_style = new IconButtonStyle;
    setStyle(m_style);

    //fix push button use as icon caused color issues
    this->setProperty("isIcon", true);
    setAttribute(Qt::WA_TranslucentBackground);

    auto shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(20);
    shadowEffect->setOffset(0, 0);
    setGraphicsEffect(shadowEffect);
}


IconButton::~IconButton()
{
    m_style->deleteLater();
}


void IconButton::paintEvent(QPaintEvent *e) {
    //QPainter p(this);
    //p.fillRect(this->rect(), this->palette().base());
    //p.setPen(this->palette().dark().color());
    //p.drawRect(this->rect().adjusted(0, 0, -1, -1));
    QPushButton::paintEvent(e);
}

IconButtonStyle::IconButtonStyle() : QProxyStyle()
{

}

void IconButtonStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    QStyleOptionButton opt = *qstyleoption_cast<const QStyleOptionButton *>(option);
    opt.palette.setColor(QPalette::Highlight, Qt::transparent);
    return QProxyStyle::drawControl(element, &opt, painter, widget);
}
