#include "helpView.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>


HelpView::HelpView(QWidget *parent) : QWidget(parent)
{
    QString gameRules = "Les règles du jeu sont simples. Chaque joueur dirige une trace d'une couleur choisie par le joueur. Les traces des joueurs apparaissent sur le terrain à des endroits définis aléatoirement. Une fois la partie débutée, le joueur dirige sa trace et devra éviter les collisions avec les bords du terrain ou la trace d'un autre joueur. Chaque seconde en vie rapport des points. Le premier joueur à 500 points gagne la partie.";
    lbRules = new QLabel(this);
    lbRules->setWordWrap(true);
    lbRules->setText(gameRules);
    btnBack = new QPushButton("Retour", this);
    grid = new QGridLayout(this);
    grid->addWidget(lbRules, 0, 0);
    grid->addWidget(btnBack, 1, 0);

    connect(btnBack, &QPushButton::clicked, this, [=](){ emit changeToMainMenuView(); });
}


