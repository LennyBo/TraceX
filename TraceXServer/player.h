#ifndef PLAYER_H
#define PLAYER_H
#include <QtCore>
#include <QPen>
#include <QGraphicsItem>
#include <Constants.h>
#include <iostream>
#include <QtNetwork>

enum directions{
    left = 0,
    straight = 1,
    right = 2
};

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QString name,int id);
    double getHeading() const;
    void setDirection(enum directions d);
    //double getSpeed();
    void tick();
    void addPoint(QPointF* point);
    void kill();
    void reset();
    int getID() const;
    bool getReady();
    void setID(bool accept,int id);
    QString getName() const;
    void setName(bool accept,QString name);
    void wonRound();
    ~Player();

    int getScore() const;
    QList<QGraphicsLineItem*> getLines() const;
    QList<QGraphicsLineItem*> getNewLines() const;
    void resetNewLines();
    void setTCPSocket(QTcpSocket *clientSocket);
    bool isAlive();
    QByteArray static sendPlayers(const QList<Player*> &players);
    void sendByteArray(const QByteArray &block);
    bool getIsConnected();
    quint16 getScore();

public slots:
    void tcpReceive();
    void tcpClose();    

signals:
    void playerLeave(Player* p);
    void playerSetName(QString name,Player* p);
    void playerSetColor(int colorID,Player* p);

    void playerReady(bool ready);

    //const QMap<int, QList<QString>> KEYS {{ 0, {"A", "D"}}, {1, {"<", ">"}}, {2, {"J", "L"}}};

    void scoreChanged(int score);
    void nameChanged(QString name);
    void colorChanged(int colorID);

private:
    QTcpSocket *clientSocket = nullptr;
    QDataStream in;

    QByteArray block;
    QDataStream out;

    void getNewSpawn();
    QPointF *head;
    QList<QGraphicsLineItem*> trace;
    QList<QGraphicsLineItem*> newTraceToSend; //Keep a pointer to all lines we didn't send yet for the next update
    QColor color;
    double heading; //Degree
    double speed;
    static QPen pens[MAX_PLAYER_COUNT];
    QString name;
    bool alive;
    int colorID;
    double score;
    bool isReady;

    bool isConnected;

    enum directions direction; // -1:LEFT   0:Straight  1:right

};
QDataStream &operator>> (QDataStream&, Player&);
QDataStream &operator<< (QDataStream&, const Player&);

#endif // PLAYER_H
