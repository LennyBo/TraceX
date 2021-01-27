#include "gameview.h"

#include "widgetplayer.h"
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>

#include "QLabel"
#include "QBoxLayout"
#include "gamegraphicsview.h"

#define SCALE_VIEW 1

GameView::GameView(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    this->setLayout(mainLayout);

    scoreLayout = new QVBoxLayout();
    scoreLayout->setAlignment(Qt::AlignTop);

    playerLayout = new QVBoxLayout();
    playerLayout->setAlignment(Qt::AlignTop);

    lblTitle = new QLabel(tr("Score"),this);
    lblTitle->setObjectName("h1");

    game = new GameGraphicsView(this);

    btnReady = new QPushButton("Prêt ?");

    connect(btnReady,&QPushButton::clicked,this,[=]
    {
        foreach(TraceXClient* client,game->getGameClient())
        {
            client->readyUp(true);
        }
        btnReady->setVisible(false);
    });

    mainLayout->addWidget(game);
    mainLayout->addLayout(scoreLayout);

    scoreLayout->addWidget(lblTitle);
    scoreLayout->addLayout(playerLayout);
    scoreLayout->addWidget(btnReady);
}

/**
 * GameView::updatePlayers
 * Delete and redraw all players (Allow to remove players who are disconnected of view)
 * @param QList<player*> list : list of players connected
 */
void GameView::updatePlayers(QList<player*> list)
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

/**
 * GameView::startGame
 *Add gameClient to GraphicsView to start game
 *
 * @param QList<TraceXClient*> g : New GameClient
 */
void GameView::startGame(QList<TraceXClient*> gameClient)
{
    game->startGame(gameClient);

    connect(gameClient.first(),&TraceXClient::updateScore,this,&GameView::updatePlayers);

    game->scale(SCALE_VIEW,SCALE_VIEW);
    game->setFixedSize(GAME_SIZE*SCALE_VIEW + MARGIN_GRAPHICSVIEW,GAME_SIZE*SCALE_VIEW+MARGIN_GRAPHICSVIEW);
}
