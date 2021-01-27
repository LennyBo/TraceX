#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QList>
#include <QTcpServer>

class Player;

class TCPServerWidget : public QGraphicsView
{
    Q_OBJECT

public:
    TCPServerWidget(QWidget *parent = nullptr);
    ~TCPServerWidget();

    QList<Player*> getPlayers();

    void newConnection();

public slots:
    void tick();

    void playerSetName(QString str,Player* p);
    void playerSetColor(int id, Player* p);
    void playerLeft(Player* p);

    void checkStart(bool ready);

signals:
    void playerAdded(Player *p);
    void playerRemoved();

private:
    QGraphicsScene *scene = nullptr;
    QGraphicsRectItem *sceneRect = nullptr;

    QTcpServer *tcpServer = nullptr;
    QList<Player*> players;

    QTimer *gameTimer = nullptr;
    QTimer *scoreTimer = nullptr;
    int tickCount;

    void initServer();
    void startGame();
    void checkCollide();
    void checkAlive();
    void resetGame();
    void sendScores();
    void sendNewLines();
    void getScores(QDataStream &out);

    int getFreeColor();
    bool isFreeColor(int colorID);



};
#endif // WIDGET_H
