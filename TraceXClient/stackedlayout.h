#ifndef STACKEDLAYOUT_H
#define STACKEDLAYOUT_H

#include <QWidget>

class QStackedLayout;

class StackedLayout : public QWidget
{
    Q_OBJECT
public:
    StackedLayout(QWidget *parent = nullptr);

private:
    QStackedLayout *stacked;   
};

#endif // STACKEDLAYOUT_H
