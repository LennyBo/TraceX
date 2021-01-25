#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QObject>
#include <QWidget>
#include "tracexclient.h"

class QLabel;
class QGridLayout;
class QLineEdit;
class QVBoxLayout;
class QGridLayout;
class ComboBoxColor;
class QPushButton;

class NetworkView : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkView(QWidget *parent = nullptr);
    QLabel *lblTitle;
    QLineEdit *fldPlayer;
    QGridLayout *grid;
    QVBoxLayout *layout;
    ComboBoxColor *cbColorPicker;
    QPushButton *btnNewGame, *btnJoinGame, *btnBack;
    QLineEdit *fldIP;

public slots:
    void sendToServer();

signals:
    void changeToMainMenuView();
    void changeToGameView();
    void addGameClient(TraceXClient* g);
};

#endif // NETWORKVIEW_H
