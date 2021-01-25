#ifndef GAMEGRAPHICSVIEW_H
#define GAMEGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "tracexclient.h"

class GameGraphicsView: public QGraphicsView
{
    Q_OBJECT

public:
    GameGraphicsView(QWidget *parent = nullptr);
    ~GameGraphicsView();
    QList<TraceXClient*> getGameClient();

public slots:
    void startGame(QList<TraceXClient*> g);
    void newLines(QList<QGraphicsLineItem*> &items);
    void duplicateLines(QList<QGraphicsLineItem*> &items); //Deletes them
    void deleteGraphicsItems();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QList<TraceXClient*> gameClient;
    QGraphicsScene *scene = nullptr;
    QGraphicsRectItem *sceneRect = nullptr;
};

#endif // GAMEGRAPHICSVIEW_H
