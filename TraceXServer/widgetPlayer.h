#ifndef VIEWPLAYER_H
#define VIEWPLAYER_H

#include <QWidget>
#include "player.h"

class QLabel;
class QHBoxLayout;

class WidgetPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetPlayer(Player *p,QWidget *parent = nullptr);
    QLabel* lblScore;
    QWidget* lblColor;
    QLabel* lblName;

public slots:
    void updateScore(int score);
    void updateName(QString name);
    void updateColor(int colorID);

};

#endif // VIEWPLAYER_H
