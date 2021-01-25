#ifndef HELPVIEW_H
#define HELPVIEW_H

#include <QObject>
#include <QWidget>

class QLabel;
class QPushButton;
class QGridLayout;

class HelpView : public QWidget
{
    Q_OBJECT
public:
    explicit HelpView(QWidget *parent = nullptr);

    QLabel *lbRules;
    QPushButton *btnBack;
    QGridLayout *grid;

signals:
    void changeToMainMenuView();
};

#endif // HELPVIEW_H
