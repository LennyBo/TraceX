#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
#include <QDebug>

#include "networkView.h"
#include "comboBoxColor.h"


NetworkView::NetworkView(QWidget *parent) : QWidget(parent)
{
    lblTitle = new QLabel(tr("Paramètres des joueurs"), this);
    lblTitle->setObjectName("h1");

    fldPlayer = new QLineEdit(this);
    cbColorPicker = new ComboBoxColor(this);

    btnNewGame = new QPushButton(tr("Créer une nouvelle partie"), this);
    btnJoinGame = new QPushButton(tr("Joindre une partie"), this);

    QLabel *lbIP = new QLabel(tr("Adresse IP"), this);
    fldIP = new QLineEdit("127.0.0.1",this);

    btnBack = new QPushButton(tr("Retour"));
    QPushButton *playBtn = new QPushButton("Jouer !");

    QHBoxLayout *playerLayout = new QHBoxLayout();
    QVBoxLayout *IPLayout = new QVBoxLayout();

    //playerLayout->setStretch()
    //lbIP->setMaximumWidth(100);
    fldIP->setMaximumWidth(500);


    IPLayout->addWidget(lbIP);
    IPLayout->addWidget(fldIP);

    playerLayout->addWidget(fldPlayer);
    playerLayout->addWidget(cbColorPicker);
    //playerLayout->addWidget(player);

    grid = new QGridLayout(this);
    grid->addWidget(lblTitle, 0, 0,1,2);
    //grid->addWidget(player, 1, 0);
    //grid->addWidget(colorPicker, 1, 1);
    grid->addLayout(playerLayout, 1, 0, 1, 2);
    grid->addWidget(btnNewGame, 2, 0);
    grid->addWidget(btnJoinGame, 2, 1);
    grid->addLayout(IPLayout, 3, 1);
    grid->addWidget(btnBack, 4, 0);
    grid->addWidget(playBtn, 4, 1);


    connect(playBtn, &QPushButton::clicked, this, &NetworkView::sendToServer);
    connect(btnBack, &QPushButton::clicked, this, [=](){ emit changeToMainMenuView() ;});
}

void NetworkView::sendToServer()
{

    TraceXClient *gameClient = new TraceXClient();
    gameClient->connectToServer(fldIP->text(),8080,fldPlayer->text(), cbColorPicker->currentIndex()-1);
    //Connection accepted

    connect(gameClient, &TraceXClient::connectionSuccess, this, [=](bool isAccepted){emit changeToGameView(); emit addGameClient(gameClient);});

    //changeDisplay();

    //emit addGameClient(gameClient);
    //emit changeToGameView();

}
