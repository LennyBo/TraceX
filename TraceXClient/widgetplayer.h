#ifndef WIDGETPLAYER_H
#define WIDGETPLAYER_H

#include <QWidget>

class QLabel;

class WidgetPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetPlayer(QString namePlayer, int playerID,int score,QWidget *parent = nullptr);
    QLabel* lblScore;

public slots:
    void updateScore(int score);

};

#endif // WIDGETPLAYER_H
