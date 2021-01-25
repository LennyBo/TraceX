#include "widgetplayer.h"
#include <QHBoxLayout>
#include <QPainterPath>
#include <QLabel>
#include <QFrame>
#include <QColor>
#include "constants.h"

#define sizeDot 20

WidgetPlayer::WidgetPlayer(QString namePlayer, int playerID,int score, QWidget* parent) : QWidget(parent)
{


    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    this->setLayout(mainLayout);

    QWidget* lblColor = new QWidget(this);
    lblColor->setFixedSize(sizeDot,sizeDot);

    QPainterPath path;
    path.addRoundedRect(lblColor->rect(), sizeDot/2, sizeDot/2);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    lblColor->setMask(mask);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, COLORS[playerID+1]);

    lblColor->setAutoFillBackground(true);
    lblColor->setPalette(pal);

    QLabel* lblName = new QLabel(namePlayer, this);
    lblScore = new QLabel("0", this);


    mainLayout->addWidget(lblColor);
    mainLayout->addWidget(lblName);
    mainLayout->addWidget(lblScore);


    lblScore->setText(QString::number(score));
    //connect(p, &Player::scoreChanged, this, &WidgetPlayer::updateScore);
}

void WidgetPlayer::updateScore(int score)
{
    lblScore->setText(QString::number(score));
}
