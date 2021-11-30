#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "GameBoard.h"
#include "playerBead.h"


class Game : public QGraphicsView
{
    Q_OBJECT
public:
    // public methods
    Game();
    void pickUpBead(playerBead *bead);
    void placeBead(nutralBead *nbead);
    void nextPlayersTurn();
    void displayMainMenu();
    void gameOver();

    // public parameters
    QGraphicsScene *scene;
    GameBoard *board;
    int totalTurn = 6;

    //getters and setters
    const QString &getWhosTurn() const;
    void setWhosTurn(const QString &newWhosTurn);

    playerBead *getBeadToPlace() const;
    void setBeadToPlace(playerBead *newBeadToPlace);

public slots:
    void start();
    void replay();
private:
    // private methods
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void drawPlayerBeads(int y,QString player);
    bool isPosCorrect(int ppos, int npos);

    // private parameters
    QString whosTurn;
    QGraphicsPixmapItem* whosTurnText;
    QList <playerBead*> player1Beads;
    QList <playerBead*> player2Beads;
    playerBead *beadToPlace;
    QPointF orgPos;

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // GAME_H
