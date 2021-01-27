#include "widgetplayer.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QColor>
#include <QPainterPath>

#include "player.h"

#define sizeDot 20

WidgetPlayer::WidgetPlayer(Player *p, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    dotColorWidget = new QWidget(this);
    dotColorWidget->setFixedSize(sizeDot,sizeDot);

    QPainterPath path;
    path.addRoundedRect(dotColorWidget->rect(), sizeDot/2, sizeDot/2);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    dotColorWidget->setMask(mask);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, COLORS[p->getID()]);

    dotColorWidget->setAutoFillBackground(true);
    dotColorWidget->setPalette(pal);    

    lblName = new QLabel(p->getName(), this);
    lblScore = new QLabel(QString::number(p->getScore()), this);

    mainLayout->addWidget(dotColorWidget);
    mainLayout->addWidget(lblName);
    mainLayout->addWidget(lblScore);

    this->setLayout(mainLayout);

    connect(p, &Player::scoreChanged, this, &WidgetPlayer::updateScore);
    connect(p, &Player::nameChanged, this, &WidgetPlayer::updateName);
    connect(p, &Player::colorChanged, this, &WidgetPlayer::updateColor);
}

void WidgetPlayer::updateScore(int score)
{
    lblScore->setText(QString::number(score));
}

void WidgetPlayer::updateName(QString name)
{
    lblName->setText(name);
}

void WidgetPlayer::updateColor(int colorID)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, COLORS[colorID]);
    dotColorWidget->setPalette(pal);
}
