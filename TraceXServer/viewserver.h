#ifndef VIEWSERVER_H
#define VIEWSERVER_H

#include <QWidget>
#include "player.h"
class QVBoxLayout;
class TCPServerWidget;

class ViewServer : public QWidget
{
    Q_OBJECT
public:
    explicit ViewServer(QWidget *parent = nullptr);
    QVBoxLayout *playersLayout;

    void addPlayer(Player *p);
    void removePlayer();

    TCPServerWidget* tcpServerWidget;

signals:

};

#endif // VIEWSERVER_H
