#ifndef WIDGETPLAYER_H
#define WIDGETPLAYER_H

#include <QWidget>

class QLabel;
class QHBoxLayout;

class WidgetPlayer : public QWidget
{
    Q_OBJECT
public:
    WidgetPlayer(QString namePlayer, int playerID,int score,QWidget *parent = nullptr);

private:
    QHBoxLayout* mainLayout;
    QWidget* dotColorWidget;
    QLabel* lblName, *lblScore;
};

#endif // WIDGETPLAYER_H
