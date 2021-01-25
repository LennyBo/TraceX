#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <QWidget>

// Forward declaration
class QPushButton;
class QVBoxLayout;
class QLabel;
class QGridLayout;

class MainMenuView : public QWidget
{
    Q_OBJECT

public:
    MainMenuView();

    QPushButton *btnLocalGame, *btnNetworkGame, *btnHelp;
    QLabel *lblTitle;
    QGridLayout *grid;

signals:
    void changeToLocalView();
    void changeToNetworkView();
    void changeToHelpView();
};

#endif // MAINMENUVIEW_H
