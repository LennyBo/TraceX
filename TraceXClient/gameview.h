#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include "constants.h"

class GameGraphicsView;
class TraceXClient;
class QHBoxLayout;
class QPushButton;

class QVBoxLayout;

class gameView : public QWidget
{
    Q_OBJECT
public:
    explicit gameView(QWidget *parent = nullptr);
    QHBoxLayout* mainLayout ;
    QVBoxLayout* playerLayout;
    QPushButton *btnReady;

    GameGraphicsView *game;

public slots:
    void updatePlayers(QList<player*> list);
    void startGame(QList<TraceXClient*> gameClient);
};

#endif // GAMEVIEW_H
