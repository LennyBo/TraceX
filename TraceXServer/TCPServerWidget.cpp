#include "TCPServerWidget.h"
#include "player.h"
#include <QMessageBox>
#include <QtNetwork>
#include <QRandomGenerator>

TCPServerWidget::TCPServerWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    initServer();

    scene = new QGraphicsScene(this);
    setScene(scene);

    resize(GAME_SIZE, GAME_SIZE);
    QRectF sceneRectF(0,0,GAME_SIZE,GAME_SIZE);
    setSceneRect(sceneRectF);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing, true);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode( QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    sceneRect = scene->addRect(sceneRectF);


    //Since we don't send scores as fast as lines, we have a seperate timer for score
    scoreTimer = new QTimer(this);
    connect(scoreTimer, &QTimer::timeout, this, [=]{
        this->sendScores();
    });
    scoreTimer->start(TIME_TO_SCORE_UPDATE);

}


/**
* TCPServerWidget::initServer()
* opens a tcp socket on TCPServerWidget::tcpServer
*/
void TCPServerWidget::initServer()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any,DEFAULT_PORT)) {
        QMessageBox::critical(this, tr("TraceXServer"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << "TCP socket listening on on :" << tcpServer->serverPort();

    connect(tcpServer, &QTcpServer::newConnection, this, &TCPServerWidget::newConnection);
}


/**
* TCPServerWidget::newConnection()
* is a slot.
* Called when a client is opening a connection with the server
* Adds a player to the QList<player*> players
* gives it the socket and makes connections
*/
void TCPServerWidget::newConnection(){
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
    qDebug() << "A client is trying to connect from: " << clientConnection->peerAddress();
    if(players.size() < MAX_PLAYER_COUNT){
        players.append(new Player("Player 1",getFreeColor()));
        emit playerAdded(players.back());
        players.back()->setTCPSocket(clientConnection);
        connect(players.back(),&Player::playerLeave,this,&TCPServerWidget::playerLeft);
        connect(players.back(),&Player::playerSetColor,this,&TCPServerWidget::playerSetColor);
        connect(players.back(),&Player::playerSetName,this,&TCPServerWidget::playerSetName);
        connect(players.back(),&Player::playerReady,this,&TCPServerWidget::checkStart);
    }else{
        qDebug() << "Server is full, kicking player";
        clientConnection->close();
    }

    //connect(clientConnection,&QAbstractSocket::re)
}


/**
* TCPServerWidget::resetGame()
* Resets all players then strarts the gameTimer
*/
void TCPServerWidget::resetGame()
{

    foreach(Player* p, players)
    {
        //if disconnected
        //remove
        p->reset();
    }
    startGame();
}

/**
* TCPServerWidget::startGame()
* starts the gameTimer
* If you want to start the timer. it is advised to use TCPServerWidget::resetGame() insetead
* as this also makes sure the players are reset
*/
void TCPServerWidget::startGame()
{
    /*scene->removeItem(sceneRect);
    scene->clear();
    scene->addItem(sceneRect);*/
    if(gameTimer == nullptr){
        gameTimer = new QTimer(this);
        connect(gameTimer, &QTimer::timeout, this, &TCPServerWidget::tick);
    }
    gameTimer->start(TIME_TO_TICK);
}


/**
* TCPServerWidget::checkStart(bool ready)
* is a slot called when a player sends readyUp command
* checks if all players are ready to start the game
* if so->starts the game after 2 seconds
*
* @param bool ready : true if the player is ready, false if not ready
*/
void TCPServerWidget::checkStart(bool ready){
    if(players.count() < 2)
        return;
    foreach(Player* p, players)
    {
        if(!p->getReady()){ //if one player is not ready we don't start
            return;
        }
    }
    qDebug() << "All payers are ready, Starting timer";
    QTimer::singleShot(DELAY_BETWEEN_ROUND,this,[=]{resetGame();});
}


/**
* TCPServerWidget::tick()
* Is called every tick of the timer.
* Updates all players
*/
void TCPServerWidget::tick()
{
    foreach(Player* p, players)
    {
        //just for test collides
        /*if(rand() %2 == 0){
            p->setDirection(static_cast<directions>(rand() %3 -1));
        }*/

        p->tick();
        if(p->getLines().count() > 0 && !scene->items().contains(p->getLines().last()))
        {
            //scene->addItem(p->getLines().last());
            scene->addItem(p->getLines().last());
        }
    }
    checkCollide();
    checkAlive();

    sendNewLines();
}

/**
* TCPServerWidget::sendScores()
* Is called on every scoreTimer tick
* sends score name and color of all connected players to all players
*/
void TCPServerWidget::sendScores(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << QString("updatePlayers");
    out << (quint8)players.count();

    getScores(out);
    foreach(Player* p, players)
    {
        p->sendByteArray(block);
    }
}

/**
* TCPServerWidget::getScores(QDataStream &out)
* writes on a data stream all the scores
*
* @param QDataStream &out : stream to write to
*/
void TCPServerWidget::getScores(QDataStream &out){
    foreach(Player* p, players){
        out << (QString)p->getName() << (quint8) p->getID() << (quint16)p->getScore();
    }
}

/**
* TCPServerWidget::sendNewLines()
* Sends all new lines to all clients so they can display it
* on their view
*/
void TCPServerWidget::sendNewLines(){
    QByteArray block = Player::sendPlayers(players);
    foreach(Player* p, players)
    {
        p->resetNewLines();
        p->sendByteArray(block);
    }
}


/**
* TCPServerWidget::getFreeColor()
*
* @returns a color that is free
*/
int TCPServerWidget::getFreeColor(){
    int colorID = -1;
    while(!isFreeColor(++colorID) && colorID < MAX_PLAYER_COUNT);

    return colorID;
}

/**
* TCPServerWidget::getFreeColor()
*
* @param int colorID : color to checkeck
* @returns true if it is free
*/
bool TCPServerWidget::isFreeColor(int colorID){
    foreach(Player* p, players){
        if(p->getID() == colorID){
            return false;
        }
    }
    return true;
}

/**
* TCPServerWidget::checkAlive()
* checks if there is stil a player alive, if so,
* end of the game is over and we restart
* on their view
*/
void TCPServerWidget::checkAlive()
{
    Player* winner = nullptr;
    foreach(Player* p, players)
    {
        if(p->isAlive() && winner == nullptr)
        {
            winner = p;
        }else if(p->isAlive() && winner != nullptr)
        {
            return; //More than 1 alive
        }
    }
    if(winner != nullptr){
        winner->wonRound();
    }
    gameTimer->stop();
    QTimer::singleShot(DELAY_BETWEEN_ROUND,this,&TCPServerWidget::resetGame);
}

QList<Player*> TCPServerWidget::getPlayers()
{
    return players;
}

void TCPServerWidget::checkCollide()
{
    foreach(Player* p, players)
    {
        if(p->isAlive()){
            QGraphicsLineItem* head = p->getLines().last();

            if(!head->collidesWithItem(sceneRect,Qt::ContainsItemBoundingRect))
            {
                p->kill();
            }

            foreach(Player* adv, players)
            {
                QList<QGraphicsLineItem*> lineCollide;
                lineCollide = adv->getLines();
                if(adv == p)
                {
                    lineCollide = adv->getLines();
                    for(int i = 0 ; i < MARGIN_COLLIDE ; i++)
                    {
                        if (!lineCollide.isEmpty())
                        {
                            lineCollide.removeLast();
                        }
                    }
                }

                foreach(QGraphicsLineItem* l, lineCollide)
                {
                    if(head->collidesWithItem(l))
                    {
                        p->kill();
                    }
                }
            }
        }
    }
}

TCPServerWidget::~TCPServerWidget()
{

}

/**
* TCPServerWidget::playerSetColor(int id, Player* p)
* Is a slot called when a player sends colorSet command
* checks if the color choosen is already taken. if so, the player gets notified
* else, we accept and send colorAccept back
*
* @param int id : the color id
* @param Player* p : pointer to the player trying to change name
*/
void TCPServerWidget::playerSetColor(int id, Player* p)
{
    QList<Player*>::iterator i;
    for(i = players.begin();i != players.end();++i){
        Player* pI = *i;
        if(pI != p && pI->getID() == id){
            p->setID(false,id);
            return;
        }
    }
    p->setID(true,id);
}


/**
* TCPServerWidget::playerSetName(QString str,Player* p)
* Is a slot called when a player sends nameSet command
* checks if the color choosen is already taken. if so, the player gets notified
* else, we accept and send nameAccept back
*
* @param QString str : Choosen name
* @param Player* p : pointer to the player trying to change color
*/
void TCPServerWidget::playerSetName(QString str,Player* p){
    QList<Player*>::iterator i;
    for(i = players.begin();i != players.end();++i){
        Player* pI = *i;
        if(pI != p && pI->getName() == str){
            //Dont accept
            p->setName(false,str);
            return;
        }
    }
    //Accept
    p->setName(true,str);
}


/**
* TCPServerWidget::playerLeft(Player* p)
* slot called when client closed the connection
*
* @param Player* p : Player that closed the connection
*/
void TCPServerWidget::playerLeft(Player* p)
{
    players.removeOne(p);
    emit playerRemoved();
    delete(p);
    /*if(!p->getIsConnected())
    {
        p->kill();
    }

    if(players.count() == 0){
        timer->stop(); //TODO make a stop function
    }*/
    qDebug() << "player count : " << players.size();
    if(players.count() == 0){
        gameTimer->stop();
    }
}

