#ifndef PLAYERBEAD_H
#define PLAYERBEAD_H

#include <QGraphicsPixmapItem>

class playerBead : public QGraphicsPixmapItem
{
public:
    playerBead(QGraphicsItem* parent= 0);

    //getters and setters

    const QString &getOwner() const;
    void setOwner(const QString &newOwner);

    int getBeadPos() const;
    void setBeadPos(int newBeadPos);

    bool isClicked = false;
private:
    QString owner;
    int beadPos = 0;
    QString p1fileName = ":/images/player1bead.png";
    QString p2fileName = ":/images/player2bead.png";

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PLAYERBEAD_H
