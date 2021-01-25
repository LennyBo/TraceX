#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class ScoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScoreWidget(QString name, QString color, QString score, QWidget *parent = nullptr);

signals:

private:
    QGridLayout *grdLayout;
    QLabel *lblName, *lblScore;
    QWidget *wColor;
};
#endif // SCOREWIDGET_H
