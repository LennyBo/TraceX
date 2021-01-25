#include "stackedlayout.h"
#include <QDebug>
#include <QStackedLayout>
#include <QPushButton>

#include "mainMenuView.h"
#include "localView.h"
#include "networkView.h"
#include "helpView.h"
#include "gameview.h"

#include <QDebug>

StackedLayout::StackedLayout(QWidget *parent) : QWidget(parent)
{    
    stacked = new QStackedLayout(this);


    MainMenuView *mainMenu = new MainMenuView();
    LocalView *localView = new LocalView();
    NetworkView *networkView = new NetworkView();
    HelpView *helpView = new HelpView();


    gameView *gameview = new gameView();

    //gameview->updatePlayers("tt", 0);
    //gameview->updatePlayers("jj", 1);

    stacked->addWidget(mainMenu);
    stacked->addWidget(localView);
    stacked->addWidget(networkView);
    stacked->addWidget(helpView);
    stacked->addWidget(gameview);

    stacked->setCurrentIndex(0);

    connect(mainMenu, &MainMenuView::changeToLocalView, this, [=](){ stacked->setCurrentIndex(1); });
    connect(mainMenu, &MainMenuView::changeToNetworkView, this, [=](){ stacked->setCurrentIndex(2); });
    connect(mainMenu, &MainMenuView::changeToHelpView, this, [=](){ stacked->setCurrentIndex(3) ;});
    connect(localView, &LocalView::changeToMainMenuView, this, [=](){stacked->setCurrentIndex(0); });
    connect(networkView, &NetworkView::changeToMainMenuView, this, [=](){ stacked->setCurrentIndex(0) ;});
    connect(helpView, &HelpView::changeToMainMenuView, this, [=](){ stacked->setCurrentIndex(0) ;});
    connect(localView, &LocalView::changeToGameView, this, [=](){ stacked->setCurrentIndex(4); });
    connect(networkView, &NetworkView::changeToGameView, this, [=](){ stacked->setCurrentIndex(4); });
    connect(localView, &LocalView::addGameClient, gameview, &gameView::startGame);
    //connect(networkView, &NetworkView::addGameClient, gameview, &gameView::startGame);
}
