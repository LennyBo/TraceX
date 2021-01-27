#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"

#include <QObject>
#include <QtNetwork>

class QTcpSocket;
class QGraphicsLineItem;

enum directions
{
    left = 0,
    straight = 1,
    right = 2
};

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QString name,int id);
    ~Player();

    void tick();
    void addPoint(QPointF* point);
    void kill();
    void reset();
    void wonRound();

    QList<QGraphicsLineItem*> getNewLines() const;
    void resetNewLines();
    QByteArray static sendPlayers(const QList<Player*> &players);
    void sendByteArray(const QByteArray &block);

    QString getName() const;
    double getHeading() const;
    int getID() const;
    bool getReady();
    int getScore() const;
    bool isAlive();
    bool getIsConnected();
    quint16 getScore();
    QList<QGraphicsLineItem*> getLines() const;

    void setDirection(enum directions d);
    void setID(bool accept,int id);
    void setName(bool accept,QString name);
    void setTCPSocket(QTcpSocket *clientSocket);

public slots:
    void tcpReceive();
    void tcpClose();    

signals:
    void playerLeave(Player* p);
    void playerSetName(QString name,Player* p);
    void playerSetColor(int colorID,Player* p);
    void playerReady(bool ready);

    void scoreChanged(int score);
    void nameChanged(QString name);
    void colorChanged(int colorID);

private:
    QString name;
    int colorID;
    double score;
    QPointF *head;
    double heading; //Degree
    double speed;
    bool alive;
    bool isReady;
    QTcpSocket *clientSocket = nullptr;
    bool isConnected;
    QDataStream in;
    QByteArray block;
    QDataStream out;
    QList<QGraphicsLineItem*> trace;
    QList<QGraphicsLineItem*> newTraceToSend; //Keep a pointer to all lines we didn't send yet for the next update
    enum directions direction; // -1:Left   0:Straight  1:right

    static QPen pens[MAX_PLAYER_COUNT];

    void getNewSpawn();
};

QDataStream &operator>> (QDataStream&, Player&);
QDataStream &operator<< (QDataStream&, const Player&);

#endif // PLAYER_H
