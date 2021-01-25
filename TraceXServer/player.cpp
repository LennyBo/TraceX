#include "player.h"
#include <QtMath>

QPen Player::pens[] = {QPen(COLORS[0],PLAYER_WIDTH),QPen(COLORS[1],PLAYER_WIDTH),QPen(COLORS[2],PLAYER_WIDTH),QPen(COLORS[3],PLAYER_WIDTH),QPen(COLORS[4],PLAYER_WIDTH),QPen(COLORS[5],PLAYER_WIDTH)};


Player::Player(QString name,int id)
{
    this->name = name;
    this->colorID = id;
    this->score = 0;
    this->isReady = DEFAULT_READY;
    reset();
    this->alive=false; //Kinda a HotFix but we want a player to not move until a game starts
}


/**
* Player::reset()
* empties trace
* resets default values and sets a new random spawn
* tells client to delete everything since we restart
*/
void Player::reset(){
    this->setDirection(directions::straight);

    //Delete trace
    while(trace.count() > 0){
        delete(trace.back());
        trace.pop_back();
    }
    speed = DEFAULT_SPEED;
    alive = DEFAULT_ALIVE;

    //Respawn
    getNewSpawn();

    //tell client to delete
    if(clientSocket != nullptr){
        if(clientSocket->isOpen()){
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_10);

            out << (QString)"deleteAllLines";

            clientSocket->write(block);
        }
    }
}


/**
* Player::getNewSpawn()
* sets a new random spawn with a random heading
*/
void Player::getNewSpawn(){
    if(trace.count() == 0){
        head = new QPointF(QRandomGenerator::global()->bounded(SPAWN_AREA)+SPAWN_AREA_PADDING,QRandomGenerator::global()->bounded(SPAWN_AREA)+SPAWN_AREA_PADDING);
        heading = QRandomGenerator::global()->bounded(360);
    }
    else
    {
        qDebug() << "CANT RESPAWN IF TRACE IS NOT EMPTY!!!";
    }
}

bool Player::getReady(){
    return isReady;
}

int Player::getScore() const{
    return score;
}

void Player::setDirection(enum directions d){
    direction = d;
}


bool Player::isAlive()
{
    return alive;
}

/**
* Player::tick()
* Steps the player once
*
*/
void Player::tick(){
    if(alive)
    {
        switch (direction) {
        case directions::left:
            heading+=TURN_RATE;
            break;
        case directions::right:
            heading-=TURN_RATE;
            break;
        }
        double dx = sin(qDegreesToRadians(heading))*speed;
        double dy = cos(qDegreesToRadians(heading))*speed;
        QPointF* p = new QPointF(head->x() + dx,head->y() + dy);
        addPoint(p);
        score+=SCORE_PER_TICK;
        emit scoreChanged(score);
    }
}

void Player::wonRound(){
    score+=ROUND_WIN_BONUS;
}

/**
* Player::addPoint(QPointF* point)
* Adds a new point to the trace. sets head to the new point
*
* @param QPointF* point : point to add
*/
void Player::addPoint(QPointF* point){
    if(this->head != nullptr)
    {
        trace.append(new QGraphicsLineItem(head->x(),head->y(),point->x(),point->y()));
        trace.back()->setPen(pens[colorID]);
        newTraceToSend.append(trace.back());
    }
    delete(head);
    head = point;
}

void Player::kill(){
    alive = false;
}

int Player::getID() const{
    return colorID;
}

QString Player::getName()const{
    return name;
}

/**
* Player::setID(bool accept,int id)
* sets color
* tells the client if the color has been accepted
*
* @param bool accept : true if the color is accepted, false if not
* @param int id : id that has been choosen
*/
void Player::setID(bool accept,int id){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    if(accept){
        this->colorID = id;
        emit colorChanged(id);
        out << (QString)"colorAccept" << (quint8) true;
    }else{
        out << (QString)"colorAccept" << (quint8) false;
    }
    clientSocket->write(block);
}

/**
* Player::setName(bool accept,QString name)
* sets name
* tells the client if the name has been accepted
*
* @param bool accept : true if the name is accepted, false if not
* @param QString name : name that has been choosen
*/
void Player::setName(bool accept,QString name){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << QString("nameAccept");
    if(accept){
        this->name = name;
        emit nameChanged(name);
        out << (quint8)1;
    }else{
        out << (quint8)0;
    }
    clientSocket->write(block);
}


/**
* Player::sendByteArray(const QByteArray &block)
* writes QByteArray to the socket
*
* @param const QByteArray &block : block to write
*/
void Player::sendByteArray(const QByteArray &block){
    clientSocket->write(block);
}

/**
* QList<QGraphicsLineItem*> Player::getLines() const
*
* @return returns all lines
*/
QList<QGraphicsLineItem*> Player::getLines() const{
    return trace;
}

/**
* QList<QGraphicsLineItem*> Player::getNewLines() const
*
* @return returns all lines that have not been sent yet
*/
QList<QGraphicsLineItem*> Player::getNewLines() const{
    return newTraceToSend;
}

/**
* void Player::resetNewLines()
* needs to be called when the new lines have been sent to the client
*/
void Player::resetNewLines(){
    newTraceToSend.clear();
}

quint16 Player::getScore(){
    return score;
}



void Player::setTCPSocket(QTcpSocket *clientSocket){
    this->clientSocket = clientSocket;
    isConnected = true;
    in.setDevice(clientSocket);
    in.setVersion(QDataStream::Qt_5_10);
    connect(this->clientSocket,&QAbstractSocket::readyRead,this,&Player::tcpReceive);
    connect(this->clientSocket,&QAbstractSocket::disconnected,this,&Player::tcpClose);
}

void Player::tcpReceive(){
    in.startTransaction();
    while(!in.atEnd()){
        QString strCommand;
        in >> strCommand;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_10);
        if(strCommand == "nameSet"){
            QString strName;
            in >> strName;
            qDebug() << "Received command from Player"<< name<< " : " << strCommand << " to " << strName;
            emit playerSetName(strName,this); //Send it to the manager that is going to accept or not
        }else if(strCommand == "colorSet"){
            quint8 colorID;
            in >> colorID;
            qDebug() << "Received command from Player"<< name<< " : " << strCommand << " to " << colorID;
            emit playerSetColor(colorID,this); //Send it to the manager that is going to accept or not
        }else if(strCommand == "direction"){
            quint8 sentId;
            in >> sentId;
            this->direction = static_cast<directions>(sentId); //Might be dangerous if player sends weird shit ex direction 8
        }else if(strCommand == "readyUp"){

            quint8 ready;
            in >> ready;
            isReady = ready;
            qDebug() << "Received command from Player"<< name << " : " << strCommand << " : " << ready;
            emit playerReady(ready);
        }
    }

    if(!in.commitTransaction())
    {
        qDebug() << "Error while reading stream";
    }
}

void Player::tcpClose()
{
    qDebug() << "Player " << name << " has left";
    isConnected = false;
    emit playerLeave(this);
}

Player::~Player(){
    //Delete trace
    while(trace.count() > 0){
        delete(trace.back());
        trace.pop_back();
    }
}


QDataStream &operator>>(QDataStream &out,Player &o)
{
    return out;
}

QDataStream &operator<<(QDataStream &in,const Player &o)
{
    in <<  o.getID() << o.getName();
    foreach(QGraphicsLineItem* l, o.getLines()){
        in << l->line();
    }
    return in;
}

bool Player::getIsConnected()
{
    return isConnected;
}


/**
* QByteArray Player::sendPlayers(const QList<Player*> &players)
* seralizes all players into a QByteArray
* does not clear newLines
*
* @param const QList<Player*> &players : players to serealize
* @return searlized ByteArray
*/
QByteArray Player::sendPlayers(const QList<Player*> &players){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << QString("newLines");
    out << (quint8)players.count();

    foreach(Player* p, players){
        //if(p->getNewLines().size() > 0){ //If no new lines, we dont need to send
        out << (quint8)p->getID() << (quint16)p->getNewLines().size(); //Dunno if size is necessary
        foreach(QGraphicsLineItem* l, p->getNewLines()){
            QLineF qLine = l->line();
            out << qLine;
        }
        //}
    }
    return block; //I guess since we need to broadcast to all players???
}


