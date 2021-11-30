#include "GameBoard.h"
#include "Game.h"
#include <QDebug>
#include "playerBead.h"

extern Game *game;

GameBoard::GameBoard()
{
    QPen pen;
    pen.setWidth(5);
    int sw = 320;   //starting width
    int sh = 90;   //starting height
    int ew = 1020;   //ending width
    int eh = 640;

    // Left border line
    QLineF ln1 (QPointF(sw,sh),QPointF(sw,eh));
    QGraphicsLineItem *line1 = new QGraphicsLineItem(ln1);
    line1->setPen(pen);
    game->scene->addItem(line1);

    // upper border line
    QLineF ln2 (QPointF(sw,sh),QPointF(ew,sh));
    QGraphicsLineItem *line2 = new QGraphicsLineItem(ln2);
    line2->setPen(pen);
    game->scene->addItem(line2);

    // right border line
    QLineF ln3 (QPointF(ew,sh),QPointF(ew,eh));
    QGraphicsLineItem *line3 = new QGraphicsLineItem(ln3);
    line3->setPen(pen);
    game->scene->addItem(line3);

    // bottum border line
    QLineF ln4 (QPointF(ew,eh),QPointF(sw,eh));
    QGraphicsLineItem *line4 = new QGraphicsLineItem(ln4);
    line4->setPen(pen);
    game->scene->addItem(line4);

    // center vertical line
    QLineF ln5 (QPointF(sw+(ew-sw)/2,sh),QPointF(sw+(ew-sw)/2,eh)); //find total length of line then find center of line and add intial width
    QGraphicsLineItem *line5 = new QGraphicsLineItem(ln5);
    line5->setPen(pen);
    game->scene->addItem(line5);

    // center horizontal line
    QLineF ln6 (QPointF(sw,sh+(eh-sh)/2),QPointF(ew,sh+(eh-sh)/2));
    QGraphicsLineItem *line6 = new QGraphicsLineItem(ln6);
    line6->setPen(pen);
    game->scene->addItem(line6);

    // right diagnol line
    QLineF ln7 (QPointF(sw,sh),QPointF(ew,eh));
    QGraphicsLineItem *line7 = new QGraphicsLineItem(ln7);
    line7->setPen(pen);
    game->scene->addItem(line7);

    // right diagnol line
    QLineF ln8 (QPointF(sw,eh),QPointF(ew,sh));
    QGraphicsLineItem *line8 = new QGraphicsLineItem(ln8);
    line8->setPen(pen);
    game->scene->addItem(line8);

    // adding all items in list
    lineItems.append(line1);
    lineItems.append(line2);
    lineItems.append(line3);
    lineItems.append(line4);
    lineItems.append(line5);
    lineItems.append(line6);
    lineItems.append(line7);
    lineItems.append(line8);

    //creating first row of nutral bead
    int pos = 1;
    for (int i = 0; i < 3; ++i)
    {
        nutralBead *nbead = new nutralBead(pos);
        nbead->setPos(300+330*i,60);
        game->scene->addItem(nbead);
        nbeadItems.append(nbead);
        pos++;
    }

    //creating 2nd row of nutral bead
    for (int i = 0; i < 3; ++i)
    {
        nutralBead *nbead = new nutralBead(pos);
        nbead->setPos(300+330*i,320);
        game->scene->addItem(nbead);
        nbeadItems.append(nbead);
        pos++;
    }

    //creating 3nd row of nutral bead
    for (int i = 0; i < 3; ++i)
    {
        nutralBead *nbead = new nutralBead(pos);
        nbead->setPos(300+330*i,590);
        game->scene->addItem(nbead);
        nbeadItems.append(nbead);
        pos++;
    }

    //test
   // QList<QGraphicsItem*> clist = line1->collidingItems();
    //qDebug()<<clist.size();
}

void GameBoard::makenBeadFalse()
{
    // if nbead not contain any player bead then make it false
    for (int i = 0; i < nbeadItems.size(); ++i)
    {
        QList<QGraphicsItem*> cItems = nbeadItems[i]->collidingItems();
        for (int j = 0; j < cItems.size(); ++j)
        {
            if (typeid (*(cItems[j])) == typeid (playerBead))
                nbeadItems[i]->setIsPlaced(true);
            else
                nbeadItems[i]->setIsPlaced(false);
        }
    }
}

bool GameBoard::hasWinner()
{
    QStringList str;
    for (int i = 0; i < lineItems.size(); ++i)
    {
        str.clear();
        QList<QGraphicsItem*> cItems = lineItems[i]->collidingItems();
        for (int j = 0; j < cItems.size(); ++j)
        {
            playerBead *bead = dynamic_cast<playerBead*>(cItems[j]);
            if(bead)
            {
               str.append(bead->getOwner());
            }
        }
        if(str.size() == 3)
        {
            qDebug()<<str[0]<<str[1]<<str[2];
            if(str[0] == str[1] && str[1] == str[2])
                return true;
        }
    }
    return false;
}




