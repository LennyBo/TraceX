#include "tracexclient.h"
#include "constants.h"

#include <QObject>
#include <QMessageBox>
#include <QPen>
#include <QMap>
#include <QTimer>
#include <QTcpSocket>

#include <QGraphicsItem>

QPen TraceXClient::pens[] = {QPen(COLORS[1],PLAYER_WIDTH),QPen(COLORS[2],PLAYER_WIDTH),QPen(COLORS[3],PLAYER_WIDTH),QPen(COLORS[4],PLAYER_WIDTH),QPen(COLORS[5],PLAYER_WIDTH),QPen(COLORS[6],PLAYER_WIDTH),QPen(COLORS[7],PLAYER_WIDTH),QPen(COLORS[8],PLAYER_WIDTH)};


TraceXClient::TraceXClient(int keyLeft,int keyRight):QObject()
{
    tcpSocket = nullptr;
    this->keyLeft = keyLeft; //Default keys
    this->keyRight = keyRight;
    isKeysPressed[0] = false;
    isKeysPressed[1] = false;

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&TraceXClient::sendKeys);
    timer->start(TIME_TO_SEND_DIRECTION);
}

/**
 * TraceXClient::sendKeys
 * Sends to server if player go straight, turn left or turn right
 */
void TraceXClient::sendKeys()
{
    if(tcpSocket->isOpen())
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_10);
        out << (QString)"direction";
        if((isKeysPressed[0] && isKeysPressed[1]) || (!isKeysPressed[0] && !isKeysPressed[1]))
        {
            //Straight
            out << quint8(directions::straight);
        }
        else if(isKeysPressed[0])
        {
            //Left
            out << quint8(directions::left);
        }
        else if(isKeysPressed[1])
        {
            //Right
            out << quint8(directions::right);
        }
        tcpSocket->write(block);
    }
}

/**
 * TraceXClient::keyPressEvent
 * Event called when user press key, save the key (left or right) that has been pressed
 *
 * @param int key : Key pressed
 */
void TraceXClient::keyPressEvent(int key)
{
    if(key == keyRight)
    {
        isKeysPressed[0] = true;

        //sendKeys();
    }
    else if(key == keyLeft)
    {
        isKeysPressed[1] = true;
        //sendKeys();
    }
}

/**
 * TraceXClient::keyPressEvent
 * Event called when user press key, save the key (left or right) that has been realeased
 *
 * @param int key : Key released
 */
void TraceXClient::keyRealeaseEvent(int key)
{
    if(key == keyRight)
    {
        isKeysPressed[0] = false;

        //sendKeys();
    }
    else if(key == keyLeft)
    {
        isKeysPressed[1] = false;
    }
}


/**
 * TraceXClient::checkConnectionAccpet
 * Checks if connection have been accepted
 */
void TraceXClient::checkConnectionAccpet()
{
    if(nameAccepted == 1 && colorAccpeted == 1)
    {
        emit connectionSuccess(true);
    }
    else if(nameAccepted == -1 || colorAccpeted == -1)
    {
        emit connectionSuccess(false);
    }    
}

/**
 * TraceXClient::receive
 * Decodes the information received
 */
void TraceXClient::receive()
{
    in.startTransaction();
    while(!in.atEnd())
    {
        QString str;
        in >> str;

        if(str == "nameAccept")
        {
            qDebug() << str;
            qint8 a;
            in >> a;
            if(a != 0)
            {
                qDebug() << "name has been accepted";
                nameAccepted = 1;

            }
            else
            {
                qDebug() << "name has not been accepted";
                nameAccepted = -1;
                tcpSocket->close();
            }
            checkConnectionAccpet();
        }
        else if(str == "colorAccept")
        {
            qDebug() << str;
            qint8 a;
            in >> a;
            if(a != 0)
            {
                qDebug() << "color has been accepted";
                colorAccpeted = 1;
            }
            else
            {
                qDebug() << "color is already taken, setting a free color instead";
                colorAccpeted = 1;     
            }
            checkConnectionAccpet();
        }
        else if(str == "newLines")
        {
            //Send "newLines"
            //For each player
            //Send id
            //Send amount of lines?
            //For each new line
            //Send all lines
            //qDebug() << "New lines";
            QList<QGraphicsLineItem*> newLinesList;
            quint8 count;
            in >> count;

            for(int i = 0;i<count;i++)
            {
                quint8 colorID;
                quint16 linesCount;
                in >> colorID >> linesCount;
                if(linesCount > 2)linesCount = 0;

                for(int i = 0;i<linesCount;i++)
                {
                    QLineF line;
                    in >> line;
                    QGraphicsLineItem* gLine = new QGraphicsLineItem(line);

                    gLine->setPen(pens[colorID]);
                    newLinesList.append(gLine);
                }
            }
            emit newLines(newLinesList);
        }
        else if(str == "deleteAllLines")
        {
            qDebug() << str;
            emit deleteGraphicsItems();
        }
        else if(str == "updatePlayers")
        {
            qDebug() << str;
            QString name;
            quint8 id;
            quint8 count;
            quint16 score;
            in >> count;
            QList<player*> list;
            for(int i = 0;i<count;i++)
            {
                player* p = new player;

                list.append(p);
                in >> name >> id >> score;
                list.back()->name = (QString)name;
                list.back()->colorID = id;
                list.back()->score = score;
            }
            emit updateScore(list);
        }
    }
    if(!in.commitTransaction())
    {
        qDebug() << "Error while reading stream";
    }
}

/**
 * TraceXClient::readyUp
 * Sends to server if player is ready
 *
 * @param bool ready : True if player is ready
 */
void TraceXClient::readyUp(bool ready)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << (QString)"readyUp" << (quint8) ready;
    tcpSocket->write(block);
}


/**
 * TraceXClient::connectToServer
 * Requests to connect a new player to a server
 *
 * @param QString host : Server's IP adress
 * @param int port : Server's port
 * @param QString name : Player's name
 * @param int colorID : Player's ID color
 */
void TraceXClient::connectToServer(QString host,int port,QString name,int colorID)
{
    if(tcpSocket == nullptr)
    {
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,&QAbstractSocket::readyRead,this, &TraceXClient::receive);
        connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &TraceXClient::displayError);
        in.setDevice(tcpSocket);
        in.setVersion(QDataStream::Qt_5_10);
    }

    if(!tcpSocket->isOpen())
    {
        tcpSocket->abort();
        tcpSocket->connectToHost(host,port);
        connect(this->tcpSocket,&QAbstractSocket::disconnected,this,&TraceXClient::tcpClose);

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_10);
        out << (QString)"nameSet" << name << (QString)"colorSet" << (quint8)colorID;

        tcpSocket->write(block);

        this->colorID = colorID;
    }
    else
    {
        qDebug("Socket already open Close old connection first");
    }
}

/**
 * TraceXClient::tcpClose
 * Informs connection with server has been closed
 */
void TraceXClient::tcpClose()
{
    qDebug() << "Connection has been closed";
    qDebug() << "You have been kicked";
}

/**
 * TraceXClient::displayError
 * Informs the user of server connection errors
 * @param socketError
 */
void TraceXClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(nullptr, tr("TraceX Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(nullptr, tr("TraceX Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(nullptr, tr("TraceX Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }
}
