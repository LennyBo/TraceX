#include "gameview.h"
#include "QLabel"
#include "QBoxLayout"
#include "gamegraphicsview.h"

#include "widgetplayer.h"
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>


gameView::gameView(QWidget *parent) : QWidget(parent)
{

    mainLayout = new QHBoxLayout(this);
    this->setLayout(mainLayout);

    QVBoxLayout* scoreLayout = new QVBoxLayout(this);
    scoreLayout->setAlignment(Qt::AlignTop);

    playerLayout = new QVBoxLayout(this);
    playerLayout->setAlignment(Qt::AlignTop);

    QLabel *lblTitle = new QLabel(tr("Score"),this);
    lblTitle->setObjectName("h1");
    //game->scale(SCALE_VIEW,SCALE_VIEW);

    mainLayout->addLayout(scoreLayout);    

    scoreLayout->addWidget(lblTitle);
    scoreLayout->addLayout(playerLayout);

    btnReady = new QPushButton("Prêt ?");

    connect(btnReady,&QPushButton::clicked,this,[=]
    {
        foreach(TraceXClient* client,game->getGameClient()){
            client->readyUp(true);
        }
        btnReady->setVisible(false);
    });

    game = new GameGraphicsView(this);

    mainLayout->addWidget(game);
    scoreLayout->addWidget(btnReady);
}

void gameView::updatePlayers(QList<player*> list)
{
    while (playerLayout->count() != 0)
    {
        auto w = playerLayout->takeAt(0);
        delete(w->widget());
        delete(w);
    }
    repaint();
    foreach(auto p, list)
    {
        WidgetPlayer *vp = new WidgetPlayer(p->name, p->colorID,p->score, this);
        playerLayout->addWidget(vp);
        delete(p);
    }
}

void gameView::startGame(QList<TraceXClient*> gameClient)
{
    game->startGame(gameClient);

    connect(gameClient.first(),&TraceXClient::updateScore,this,&gameView::updatePlayers);

    game->setFixedSize(800,800);
}

