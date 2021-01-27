#include "localview.h"

#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QComboBox>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QCheckBox>

#include "comboboxcolor.h"
#include "constants.h"


LocalView::LocalView(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    IPAdressLayout = new QHBoxLayout();
    joinExternalLayout = new QHBoxLayout();
    joinExternalLayout->setAlignment(Qt::AlignLeft);

    lblTitle = new QLabel(tr("Paramètres des joueurs"), this);
    lblTitle->setObjectName("h1");
    lblExternalIP = new QLabel(tr("Rejoindre un serveur existant : "));
    mainLayout->addWidget(lblTitle);
    grid = new QGridLayout();
    grid->addWidget(lblTitle, 0, 0);
    btnBack = new QPushButton("Retour", this);
    btnPlay = new QPushButton("Jouer !");
    fldIP = new QLineEdit(this);
    fldIP->setText("127.0.0.1");
    lblIPAdress = new QLabel(this);

    for(int i = 0; i < 3; i++)
    {
        fldPlayers[i] = new QLineEdit(this);
        fldPlayers[i]->setPlaceholderText(QString("Joueur %1").arg(i+1));
        cbColorPicker[i] = new ComboBoxColor();
        grid->addWidget(fldPlayers[i], i+1, 0);
        grid->addWidget(cbColorPicker[i], i+1, 1);
        keyLabel[i] = new KeyIcon(i);
        grid->addWidget(keyLabel[i], i+1, 2);
    }
    fldPlayers[0]->setText("Joueur 1");

    fldPlayers[2]->setReadOnly(true);
    cbColorPicker[2]->setVisible(false);
    keyLabel[2]->setVisible(false);
    lblIPAdress = new QLabel();
    joinExternalLayout->addWidget(lblExternalIP);
    joinExternalLayout->addWidget(lblIPAdress);
    joinExternalLayout->addWidget(fldIP);

    grid->addWidget(btnBack, 5, 0);
    grid->addWidget(btnPlay, 5, 1, 5, 2);
    grid->addLayout(joinExternalLayout, 4, 0, Qt::AlignLeft);

    mainLayout->addLayout(grid);

    connect(btnBack, &QPushButton::clicked, this, [=]{ emit changeToMainMenuView(); });
    connect(fldPlayers[2], &QLineEdit::textEdited, this, &LocalView::enablePlayer3LineEdit);
    connect(btnPlay, &QPushButton::clicked, this, &LocalView::sendToServer);
    connect(fldPlayers[0], &QLineEdit::textEdited, this, &LocalView::enablePlayer3LineEdit);
    connect(fldPlayers[1], &QLineEdit::textEdited, this, &LocalView::enablePlayer3LineEdit);
}

void LocalView::enablePlayer3LineEdit()
{
    if(fldPlayers[0]->text().size() > 0 && fldPlayers[1]->text().size() > 0)
    {
        fldPlayers[2]->setReadOnly(false);
        if(fldPlayers[2]->text().size() > 0)
        {
            cbColorPicker[2]->setVisible(true);
            keyLabel[2]->setVisible(true);
        }
        else
        {
            cbColorPicker[2]->setVisible(false);
            keyLabel[2]->setVisible(false);
        }
    }
    else
    {
        cbColorPicker[2]->setVisible(false);
        keyLabel[2]->setVisible(false);
        fldPlayers[2]->clear();
        fldPlayers[2]->setReadOnly(true);
    }
}

/**
 * LocalView::sendToServer
 * Create game client, try to connect and change display
 */
void LocalView::sendToServer()
{
    QList<TraceXClient*> gameClients;
    for(int i = 0;i<MAX_LOCAL_PLAYERS;i++)
    {
        if(fldPlayers[i]->text() != "")
        {
            gameClients.append(new TraceXClient(KEYS[i].keyValLeft,KEYS[i].keyValRight));
            gameClients.back()->connectToServer(fldIP->text(), 8080,fldPlayers[i]->text(), cbColorPicker[i]->currentIndex() == 0 ? 0:cbColorPicker[i]->currentIndex()-1);
        }
    }

    //Connection accepted
    connect(gameClients.back(), &TraceXClient::connectionSuccess, this, [=](bool isAccepted){emit changeToGameView(); emit addGameClient(gameClients);});
}
