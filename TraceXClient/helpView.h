#ifndef HELPVIEW_H
#define HELPVIEW_H

#include <QWidget>

class QLabel;
class QPushButton;
class QGridLayout;

class HelpView : public QWidget
{
    Q_OBJECT
public:
    HelpView(QWidget *parent = nullptr);

signals:
    void changeToMainMenuView();

private:
    QGridLayout *grid;
    QLabel *lbRules;
    QPushButton *btnBack;



};

#endif // HELPVIEW_H
