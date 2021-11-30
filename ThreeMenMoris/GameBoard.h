#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QGraphicsLineItem>
#include "nutralBead.h"


class GameBoard
{
public:
    GameBoard();
    void makenBeadFalse();
    bool hasWinner();
private:
    // private parameters
    QList <QGraphicsLineItem*> lineItems;
    QList <nutralBead*> nbeadItems;
};

#endif // GAMEBOARD_H
