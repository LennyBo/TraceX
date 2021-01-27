#ifndef LOCALVIEW_H
#define LOCALVIEW_H

#include "keyicon.h"

#include <QWidget>

#include "tracexclient.h"

class ComboBoxColor;
class QLabel;
class QLineEdit;
class QGridLayout;
class QComboBox;
class QIcon;
class QVBoxLayout;
class QPushButton;
class QCheckBox;


class LocalView : public QWidget
{
    Q_OBJECT
public:
    LocalView(QWidget *parent = nullptr);

public slots:
    void enablePlayer3LineEdit();
    void sendToServer();

signals:
    void changeToMainMenuView();
    void changeToGameView();
    void textEdited();
    void clicked();
    void addGameClient(QList<TraceXClient*> g);
    void isChecked();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *IPAdressLayout, *joinExternalLayout;
    QGridLayout *grid;
    QLabel *lblTitle, *lblIPAdress, *lblExternalIP;
    KeyIcon *keyLabel[3];
    QLineEdit *fldPlayers[3], *fldIP;
    ComboBoxColor *cbColorPicker[3];
    QPushButton *btnBack, *btnPlay;
};

#endif // LOCALVIEW_H
