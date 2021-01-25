#include "widgetPlayer.h"
#include "player.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QColor>

#define sizeDot 20

WidgetPlayer::WidgetPlayer(Player *p, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);


    lblColor = new QWidget(this);
    lblColor->setFixedSize(sizeDot,sizeDot);

    QPainterPath path;
    path.addRoundedRect(lblColor->rect(), sizeDot/2, sizeDot/2);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    lblColor->setMask(mask);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, COLORS[p->getID()]);

    lblColor->setAutoFillBackground(true);
    lblColor->setPalette(pal);

    //lblColor->setStyleSheet("background-color: orange;");

    lblName = new QLabel(p->getName(), this);
    lblScore = new QLabel(QString::number(p->getScore()), this);

    mainLayout->addWidget(lblColor);
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
    lblColor->setPalette(pal);
}
