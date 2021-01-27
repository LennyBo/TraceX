#ifndef TRAXEXCLIENT_H
#define TRAXEXCLIENT_H

#include "constants.h"

#include <QObject>
#include <QAbstractSocket>
#include <QDataStream>

class QGraphicsLineItem;
class QTcpSocket;

enum directions
{
    left = 0,
    straight = 1,
    right = 2
};

class TraceXClient:public QObject
{
    Q_OBJECT
public:
    TraceXClient(int keyLeft = Qt::Key_A,int keyRight = Qt::Key_D);

    void connectToServer(QString host,int port,QString name,int colorID);
    void readyUp(bool ready);

public slots:
    void receive();
    void displayError(QAbstractSocket::SocketError socketError);
    void tcpClose();
    void keyPressEvent(int key);
    void keyRealeaseEvent(int key);
    void sendKeys();

signals:
    void newLines(QList<QGraphicsLineItem*> &items);
    void deleteGraphicsItems();
    void connectionSuccess(bool accepted);
    void updateScore(const QList<player*> &list);

protected:
    int keyLeft; //Key that we react to
    int keyRight;
    bool isKeysPressed[2];
    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    static QPen pens[NUMBER_COLORS];
    int colorAccpeted = 0; // 0 = waiting, -1 = refused, 1 = accept
    int nameAccepted = 0;
    quint8 colorID;

    void checkConnectionAccpet();
};

#endif // TRAXEXCLIENT_H
