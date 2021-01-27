#include "mainmenuview.h"

#include <QDebug>
#include <QStackedLayout>
#include <QPushButton>

#include "localview.h"
#include "helpview.h"
#include "gameview.h"
#include "stackedlayout.h"

StackedLayout::StackedLayout(QWidget *parent) : QWidget(parent)
{    
    stacked = new QStackedLayout(this);

    MainMenuView *mainMenu = new MainMenuView();
    LocalView *localView = new LocalView();    
    HelpView *helpView = new HelpView();
    GameView *gameview = new GameView();

    stacked->addWidget(mainMenu);
    stacked->addWidget(localView);    
    stacked->addWidget(helpView);
    stacked->addWidget(gameview);

    stacked->setCurrentIndex(0);

    connect(mainMenu, &MainMenuView::changeToLocalView, this, [=](){ stacked->setCurrentIndex(1); });    
    connect(mainMenu, &MainMenuView::changeToHelpView, this, [=](){ stacked->setCurrentIndex(2) ;});
    connect(localView, &LocalView::changeToMainMenuView, this, [=](){stacked->setCurrentIndex(0); });    
    connect(helpView, &HelpView::changeToMainMenuView, this, [=](){ stacked->setCurrentIndex(0) ;});
    connect(localView, &LocalView::changeToGameView, this, [=](){ stacked->setCurrentIndex(3); });
    connect(localView, &LocalView::addGameClient, gameview, &GameView::startGame);
}
