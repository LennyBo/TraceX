#include "viewserver.h"

#include <QBoxLayout>
#include <iostream>
#include <QList>
#include <QLabel>

#include "tcpserverwidget.h"
#include "widgetplayer.h"

#define SCALE_VIEW 0.5

ViewServer::ViewServer(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    playersLayout = new QVBoxLayout();

    QLabel *lblTitle = new QLabel(tr("Serveur"),this);
    lblTitle->setObjectName("h1");

    tcpServerWidget = new TCPServerWidget(this);
    tcpServerWidget->setFixedSize(GAME_SIZE*SCALE_VIEW+MARGIN_GRAPHICSVIEW,GAME_SIZE*SCALE_VIEW+MARGIN_GRAPHICSVIEW);

    tcpServerWidget->scale(SCALE_VIEW,SCALE_VIEW);

    mainLayout->addWidget(lblTitle);
    mainLayout->addLayout(playersLayout);

    mainLayout->addWidget(tcpServerWidget);

    connect(tcpServerWidget, &TCPServerWidget::playerAdded, this, &ViewServer::addPlayer);
    connect(tcpServerWidget, &TCPServerWidget::playerRemoved, this, &ViewServer::removePlayer);
}

void ViewServer::addPlayer(Player *p)
{
    WidgetPlayer *vp = new WidgetPlayer(p,this);
    playersLayout->addWidget(vp);
}

void ViewServer::removePlayer()
{
    while (playersLayout->count() != 0)
    {
        auto w = playersLayout->takeAt(0);
        delete(w->widget());
        delete(w);
    }
    repaint();

    foreach(Player *p, tcpServerWidget->getPlayers())
    {
        WidgetPlayer *vp = new WidgetPlayer(p,this);
        playersLayout->addWidget(vp);
    }
}
