#include "scorewidget.h"

ScoreWidget::ScoreWidget(QString name, QString color, QString score,QWidget *parent) : QWidget(parent)
{
    lblName = new QLabel(this);
    lblScore = new QLabel(this);
    wColor = new QWidget(this);
    QPalette pal = wColor->palette();

    pal.setColor(QPalette::Background,Qt::yellow);
    wColor->setAutoFillBackground(true);
    wColor->setPalette(pal);

}
