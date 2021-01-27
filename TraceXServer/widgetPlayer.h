#ifndef VIEWPLAYER_H
#define VIEWPLAYER_H

#include "player.h"

#include <QWidget>

class QLabel;
class QHBoxLayout;

class WidgetPlayer : public QWidget
{
    Q_OBJECT
public:
    WidgetPlayer(Player *p,QWidget *parent = nullptr);

private:
    QLabel *lblScore, *lblName;
    QWidget *dotColorWidget;

public slots:
    void updateScore(int score);
    void updateName(QString name);
    void updateColor(int colorID);
};

#endif // VIEWPLAYER_H
