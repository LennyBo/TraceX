#ifndef STACKEDLAYOUT_H
#define STACKEDLAYOUT_H

#include <QWidget>
#include <QStackedLayout>

class StackedLayout : public QWidget
{
    Q_OBJECT
public:

    StackedLayout(QWidget *parent = nullptr);
    QStackedLayout *stacked;   
};

#endif // STACKEDLAYOUT_H
