#include "nutralBead.h"
#include <Game.h>
#include <QDebug>

extern Game *game;

nutralBead::nutralBead(const int posi, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), npos(posi)
{
    setPixmap(QPixmap(fileName));
}

int nutralBead::getPos() const
{
    return npos;
}

bool nutralBead::getIsPlaced() const
{
    return isPlaced;
}

void nutralBead::setIsPlaced(bool newIsPlaced)
{
    isPlaced = newIsPlaced;
}

void nutralBead::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   // qDebug()<<"run";
    if(game->getBeadToPlace() && !isPlaced)
    {
        game->placeBead(this);
    }
}
