#include "Game.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include "Button.h"

Game::Game()
{
    // setup scene
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1080,680);
    setScene(scene);

    // setup view
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1080,680);
    setBackgroundBrush(QBrush(QImage(":/images/bg.jpg")));

    // initialize parameters
    beadToPlace = nullptr;
}

void Game::pickUpBead(playerBead *bead)
{
    // picks up the specified bead
    if (bead->getOwner() == getWhosTurn() && beadToPlace == NULL)
    {
        beadToPlace = bead;
        orgPos = bead->pos();
        return;
    }
}

void Game::placeBead(nutralBead *nbead)
{
    int npos = nbead->getPos();
    int ppos = beadToPlace->getBeadPos();

    if(isPosCorrect(ppos, npos))
    {
        board->makenBeadFalse();
        beadToPlace->setBeadPos(npos);
        beadToPlace->setZValue(0);
        nbead->setIsPlaced(true);
        beadToPlace->setPos(nbead->pos().x()+5,nbead->pos().y()+5);
        beadToPlace = nullptr;

        //check winner
        if(board->hasWinner())
            gameOver();

        //turn next player
        nextPlayersTurn();
    }
}

void Game::nextPlayersTurn()
{
    if (getWhosTurn() == QString("PLAYER1")){
        setWhosTurn(QString("PLAYER2"));
    }
    else {
        setWhosTurn(QString("PLAYER1"));
    }
}

void Game::displayMainMenu()
{
    // create the play button
    Button* playButton = new Button;
    playButton->setBtnName(QString("PLAY"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button;
    quitButton->setBtnName(QString("QUIT"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 400;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::gameOver()
{
    QString messege = "WINNER ";
    messege += getWhosTurn();
    // disable all scene items
        for (size_t i = 0, n = scene->items().size(); i < n; i++){
            scene->items()[i]->setEnabled(false);
        }

        // pop up semi transparent panel
        drawPanel(0,0,1024,768,Qt::black,0.65);

        // draw panel
        drawPanel(width()/2-250,height()/2-250,500,500,Qt::darkMagenta,0.70);

        // create playAgain button
        Button* playAgain = new Button;
        playAgain->setBtnName("REPLAY");
        int bxPos = this->width()/2 - playAgain->boundingRect().width()/2;
        int byPos = 275;
        playAgain->setPos(bxPos,byPos);
        scene->addItem(playAgain);
        connect(playAgain,SIGNAL(clicked()),this,SLOT(replay()));

        // create quit button
        Button* quit = new Button;
        quit->setBtnName("QUIT");
        int qxPos = this->width()/2 - quit->boundingRect().width()/2;
        int qyPos = 400;
        quit->setPos(qxPos,qyPos);
        scene->addItem(quit);
        connect(quit,SIGNAL(clicked()),this,SLOT(close()));

        // create text annoucning winner
        QGraphicsTextItem* overText = new QGraphicsTextItem(messege);
        QFont font("comic sans", 30);
        overText->setFont(font);
        overText->setPos(width()/2-overText->boundingRect().width()/2,200);
        scene->addItem(overText);
}

void Game::start()
{
    setBackgroundBrush(QBrush(QImage(":/images/bg2.jpg")));
    scene->clear();
    board = new GameBoard;
    drawGUI();
}

void Game::replay()
{
    // clear some stuff then call start()
    player1Beads.clear();
    player2Beads.clear();
    totalTurn = 6;
    start();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem *panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::drawGUI()
{
    // draw the left panel
    drawPanel(0,0,250,680,Qt::darkYellow,0.70);

    // place player 1 text
    QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem;
    p1->setPixmap(QPixmap(":/images/p1label.png"));
    p1->setPos(35,25);
    scene->addItem(p1);

    //draw player 1 beads
    drawPlayerBeads(100, QString("PLAYER1"));

    // place player 2 text
    QGraphicsPixmapItem *p2 = new QGraphicsPixmapItem;
    p2->setPixmap(QPixmap(":/images/p2label.png"));
    p2->setPos(35,330);
    scene->addItem(p2);

    //draw player 2 beads
    drawPlayerBeads(400, QString("PLAYER2"));

    // place whosTurnText
    whosTurnText = new QGraphicsPixmapItem;
    setWhosTurn(QString("PLAYER1"));
    whosTurnText->setPos(575,7);
    scene->addItem(whosTurnText);
}

void Game::drawPlayerBeads(int y, QString player)
{
    int xpos = 45;
    for (int i = 0; i < 3; ++i)
    {
        playerBead *bead = new playerBead;
        bead->setOwner(player);
        if(i == 2)
            bead->setPos(xpos+45,y+80);
        else
            bead->setPos(xpos+90*i,y);
        scene->addItem(bead);
        if(player == QString("PLAYER1"))
            player1Beads.append(bead);
        else if(player == QString("PLAYER2"))
            player2Beads.append(bead);
        else
            qDebug()<<"wrong player from drawPlayerBeads";
    }

}

bool Game::isPosCorrect(int ppos, int npos)
{
    switch (ppos)
    {
    case 1:
        if (npos == 2 || npos == 4 || npos == 5)
            return true;
        else
            return false;
    case 2:
        if (npos == 1 || npos == 3 || npos == 5)
            return true;
        else
            return false;
    case 3:
        if (npos == 2 || npos == 6 || npos == 5)
            return true;
        else
            return false;
    case 4:
        if (npos == 1 || npos == 5 || npos == 7)
            return true;
        else
            return false;
    case 5:
        if (npos == 1 || npos == 2 || npos == 3 || npos == 4 ||
            npos == 6 || npos == 7 || npos == 8 || npos == 9)
            return true;
        else
            return false;
    case 6:
        if (npos == 3 || npos == 5 || npos == 9)
            return true;
        else
            return false;
    case 7:
        if (npos == 4 || npos == 5 || npos == 8)
            return true;
        else
            return false;
    case 8:
        if (npos == 7 || npos == 5 || npos == 9)
            return true;
        else
            return false;
    case 9:
        if (npos == 6 || npos == 5 || npos == 8)
            return true;
        else
            return false;
    default:
        return true;
    }
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(beadToPlace)
    {
        beadToPlace->setZValue(1);
        beadToPlace->setPos(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    // make right click return cardToPlace to originalPos
    if (event->button() == Qt::RightButton){
        if (beadToPlace)
        {
            beadToPlace->setZValue(0);
            beadToPlace->setPos(orgPos);
            beadToPlace = NULL;
            return;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

playerBead *Game::getBeadToPlace() const
{
    return beadToPlace;
}

void Game::setBeadToPlace(playerBead *newBeadToPlace)
{
    beadToPlace = newBeadToPlace;
}

const QString &Game::getWhosTurn() const
{
    return whosTurn;
}

void Game::setWhosTurn(const QString &newWhosTurn)
{
    whosTurn = newWhosTurn;
    // change the QGraphicsPixmapItem
    if(newWhosTurn == QString("PLAYER1"))
        whosTurnText->setPixmap(QPixmap(":/images/p1turn.png"));
    else
        whosTurnText->setPixmap(QPixmap(":/images/p2turn.png"));
}
