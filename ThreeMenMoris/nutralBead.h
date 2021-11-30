#ifndef NUTRALBEAD_H
#define NUTRALBEAD_H

#include <QGraphicsPixmapItem>

class nutralBead : public QGraphicsPixmapItem
{

public:
    nutralBead(const int posi, QGraphicsItem* parent= 0);

    //getters and setters
    int getPos() const;

    bool getIsPlaced() const;
    void setIsPlaced(bool newIsPlaced);

private:
    const int npos = 0;
    bool isPlaced = false;
    QString fileName = ":/images/nutralbead";

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NUTRALBEAD_H
