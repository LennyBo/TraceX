#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "constants.h"

#include <QWidget>

class GameGraphicsView;
class TraceXClient;
class QHBoxLayout;
class QPushButton;
class QVBoxLayout;
class QLabel;

class GameView : public QWidget
{
    Q_OBJECT
public:
    GameView(QWidget *parent = nullptr);

private:
    QHBoxLayout* mainLayout ;
    QVBoxLayout* playerLayout, *scoreLayout;
    QPushButton *btnReady;
    GameGraphicsView *game;
    QLabel *lblTitle;

public slots:
    void startGame(QList<TraceXClient*> gameClient);

    void updatePlayers(QList<player*> list);

};

#endif // GAMEVIEW_H
