#include "Button.h"
#include <QDebug>

Button::Button()
{
    setAcceptHoverEvents(true);
}

void Button::setBtnName(QString name)
{
    if(name == QString("PLAY"))
        setPixmap(QPixmap(B1fileName));

    else if (name == QString("QUIT"))
        setPixmap(QPixmap(B2fileName));

    else if (name == QString("REPLAY"))
        setPixmap(QPixmap(B3fileName));

    else
        qDebug()<<"Wrong player";
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setPos(x()-15,y());
    setScale(1.1);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPos(x()+15,y());
    setScale(1);
}
