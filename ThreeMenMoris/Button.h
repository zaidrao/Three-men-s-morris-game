#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QObject>


class Button :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Button();
    void setBtnName(QString name);
signals:
    void clicked();
private:
    QString B1fileName = ":/images/play.png";
    QString B2fileName = ":/images/quit.png";
    QString B3fileName = ":/images/replay.png";


    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // BUTTON_H
