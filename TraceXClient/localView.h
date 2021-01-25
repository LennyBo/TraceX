#ifndef LOCALVIEW_H
#define LOCALVIEW_H

#include <QWidget>

#include "keyIcon.h"
#include "comboBoxColor.h"
#include "constants.h"

class ComboBoxColor;
class QLabel;
class QLineEdit;
class QGridLayout;
class QComboBox;
class QIcon;
class QVBoxLayout;
class QPushButton;
class QCheckBox;

#include "tracexclient.h"

class LocalView : public QWidget
{
    Q_OBJECT
public:
    explicit LocalView(QWidget *parent = nullptr);

    QLabel *lblTitle, *lblIPAdress, *lblExternalIP;
    QLineEdit *fldPlayers[3], *fldIP;
    QGridLayout *grid;
    QVBoxLayout *layout, *mainLayout;
    QHBoxLayout *IPAdressLayout, *joinExternalLayout;
    ComboBoxColor *cbColorPicker[3];
    KeyIcon *keyLabel[3];
    QPushButton *btnBack, *btnPlay;


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
};

#endif // LOCALVIEW_H
