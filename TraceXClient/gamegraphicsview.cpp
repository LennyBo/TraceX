#include "gamegraphicsview.h"

#include <QGraphicsItem>
#include <QTimer>
#include <QKeyEvent>

#include "constants.h"

GameGraphicsView::GameGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();

    QRectF sceneRectF(0,0,GAME_SIZE,GAME_SIZE);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing, true);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode( QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    setSceneRect(sceneRectF);
    setScene(scene);

    sceneRect = scene->addRect(sceneRectF);
    sceneRect->setPen(QPen(Qt::white));
}

GameGraphicsView::~GameGraphicsView() { }

/**
 * GameGraphicsView::deleteGraphicsItems
 * Removes all items from the scene
 */
void GameGraphicsView::deleteGraphicsItems()
{
    scene->clear();
}

/**
 * GameGraphicsView::newLines
 * Add new lines on scene
 *
 * @param QList<QGraphicsLineItem*> items : List of new lines
 */
void GameGraphicsView::newLines(QList<QGraphicsLineItem*> &items)
{
    foreach (QGraphicsItem* item, items)
    {
        scene->addItem(item);
    }
}

/**
 * GameGraphicsView::duplicateLines
 * @param Delete all items recieve from server that are redundants (because each gameclient recieved lines)
 */
void GameGraphicsView::duplicateLines(QList<QGraphicsLineItem*> &items)
{
    foreach (QGraphicsItem* item, items)
    {
        delete(item);
    }
}

/**
 * GameGraphicsView::getGameClient
 * Access to gameClient
 * @return gameClient
 */
QList<TraceXClient*> GameGraphicsView::getGameClient()
{
    return gameClient;
}

/**
 * GameGraphicsView::startGame
 * Add gameClient and connect each player to start the game
 * @param QList<TraceXClient*> g : New GameClient
 */
void GameGraphicsView::startGame(QList<TraceXClient*> g)
{
    this->gameClient = g;

    connect(gameClient.first(), &TraceXClient::newLines,this,&GameGraphicsView::newLines);
    connect(gameClient.first(),&TraceXClient::deleteGraphicsItems,this,&GameGraphicsView::deleteGraphicsItems);

    for(int i = 1;i<gameClient.count();i++)
    {
        connect(gameClient[i], &TraceXClient::newLines,this,&GameGraphicsView::duplicateLines);
    }
}

/**
 * @brief GameGraphicsView::keyPressEvent
 * Event called when user press key, transfered key to each TraceXClient
 *
 * @param QKeyEvent event
 */
void GameGraphicsView::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "KeyPressed " << event->key();
    if(event->isAutoRepeat())
        return;
    int key = event->key();
    foreach(TraceXClient* client,gameClient){
        client->keyPressEvent(key);
    }
}

/**
 * @brief GameGraphicsView::keyPressEvent
 * Event called when user press key, transfered key to each TraceXClient
 *
 * @param QKeyEvent event
 */
void GameGraphicsView::keyReleaseEvent(QKeyEvent *event)
{    
    if(event->isAutoRepeat())
        return;
    int key = event->key();
    foreach(TraceXClient* client,gameClient)
    {
        client->keyRealeaseEvent(key);
    }
}
