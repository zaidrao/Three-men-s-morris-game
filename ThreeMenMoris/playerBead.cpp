#include "playerBead.h"
#include <QDebug>
#include "Game.h"

extern Game *game;

playerBead::playerBead(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{

}

const QString &playerBead::getOwner() const
{
    return owner;
}

void playerBead::setOwner(const QString &newOwner)
{
    owner = newOwner;

    // check player and set image
    if(owner == QString("PLAYER1"))
        setPixmap(QPixmap(p1fileName));

    else if (owner == QString("PLAYER2"))
        setPixmap(QPixmap(p2fileName));

    else
        qDebug()<<"Wrong player";
}

int playerBead::getBeadPos() const
{
    return beadPos;
}

void playerBead::setBeadPos(int newBeadPos)
{
    beadPos = newBeadPos;
}

void playerBead::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(beadPos == 0 && game->totalTurn > 0)
    {
        game->pickUpBead(this);
        game->totalTurn--;
        return;
    }
    if(game->totalTurn == 0)
        game->pickUpBead(this);

    Q_UNUSED(event)
}

