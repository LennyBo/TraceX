#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QList>
#include <QTcpServer>
#include "player.h"

class TCPServerWidget : public QGraphicsView
{
    Q_OBJECT
private:
    QTcpServer *tcpServer = nullptr;
    void initServer();
    QGraphicsScene *scene = nullptr;
    QGraphicsRectItem *sceneRect = nullptr;
    void startGame();
    QList<Player*> players;
    void checkCollide();
    void checkAlive();
    void resetGame();
    QTimer *gameTimer = nullptr;
    QTimer *scoreTimer = nullptr;
    int tickCount;
    void sendScores();
    void sendNewLines();
    void getScores(QDataStream &out);
    int getFreeColor();
    bool isFreeColor(int colorID);

public slots:
    void tick();
    void playerLeft(Player* p);
    void playerSetColor(int id, Player* p);
    void playerSetName(QString str,Player* p);
    void checkStart(bool ready);

public:
    TCPServerWidget(QWidget *parent = nullptr);
    ~TCPServerWidget();
    void newConnection();
    QList<Player*> getPlayers();

signals:
    void playerAdded(Player *p);
    void playerRemoved();
};
#endif // WIDGET_H
