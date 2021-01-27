#include "mainmenuview.h"
#include "stackedlayout.h"

#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>


MainMenuView::MainMenuView()
{
    grid = new QGridLayout(this);
    lblTitle = new QLabel(tr("TraceX"), this);
    lblTitle->setObjectName("h1");
    btnLocalGame = new QPushButton(tr("Jouer !"), this);
    btnHelp = new QPushButton(tr("Aide"), this);
    btnHelp->setObjectName("help");

    grid->addWidget(lblTitle,1,0,1,2);
    grid->addWidget(btnLocalGame,2,0,1,2);    
    grid->addWidget(btnHelp, 0, 1);

    connect(btnLocalGame, &QPushButton::clicked, this, [=](){ emit changeToLocalView();});    
    connect(btnHelp, &QPushButton::clicked, this, [=](){ emit changeToHelpView(); });
}
