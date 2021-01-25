#include "gamegraphicsview.h"
#include <QGraphicsRectItem>
#include <QTimer>
#include <QKeyEvent>


#define GAME_SIZE 800

GameGraphicsView::GameGraphicsView(QWidget *parent) : QGraphicsView(parent)
{    
    resize(GAME_SIZE,GAME_SIZE);

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

void GameGraphicsView::deleteGraphicsItems()
{
    scene->clear();
}



void GameGraphicsView::newLines(QList<QGraphicsLineItem*> &items)
{
    foreach (QGraphicsItem* item, items)
    {
        scene->addItem(item);
    }
}

void GameGraphicsView::duplicateLines(QList<QGraphicsLineItem*> &items)
{
    foreach (QGraphicsItem* item, items)
    {
        delete(item);
    }
}

QList<TraceXClient*> GameGraphicsView::getGameClient()
{
    return gameClient;
}

void GameGraphicsView::startGame(QList<TraceXClient*> g)
{
    this->gameClient = g;

    connect(gameClient.first(), &TraceXClient::newLines,this,&GameGraphicsView::newLines);
    connect(gameClient.first(),&TraceXClient::deleteGraphicsItems,this,&GameGraphicsView::deleteGraphicsItems);

    for(int i = 1;i<gameClient.count();i++){
        connect(gameClient[i], &TraceXClient::newLines,this,&GameGraphicsView::duplicateLines);
    }
}

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

void GameGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    //qDebug() << "KeyPressed " << event->key();
    if(event->isAutoRepeat())
        return;
    int key = event->key();
    foreach(TraceXClient* client,gameClient){
        client->keyRealeaseEvent(key);
    }
}

GameGraphicsView::~GameGraphicsView()
{
}
