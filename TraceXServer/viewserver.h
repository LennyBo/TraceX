#ifndef VIEWSERVER_H
#define VIEWSERVER_H

#include <QWidget>

class Player;
class QVBoxLayout;
class TCPServerWidget;

class ViewServer : public QWidget
{
    Q_OBJECT
public:
    ViewServer(QWidget *parent = nullptr);

    void addPlayer(Player *p);
    void removePlayer();

private:
    QVBoxLayout *mainLayout, *playersLayout;
    TCPServerWidget* tcpServerWidget;

};

#endif // VIEWSERVER_H
