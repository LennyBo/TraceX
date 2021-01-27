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



signals:
    void changeToLocalView();    
    void changeToHelpView();

private:
    QGridLayout *grid;
    QLabel *lblTitle;
    QPushButton *btnLocalGame, *btnHelp;


};

#endif // MAINMENUVIEW_H
