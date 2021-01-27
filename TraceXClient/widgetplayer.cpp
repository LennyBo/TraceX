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
    mainLayout = new QHBoxLayout(this);
    this->setLayout(mainLayout);

    dotColorWidget = new QWidget(this);
    dotColorWidget->setFixedSize(sizeDot,sizeDot);

    QPainterPath path;
    path.addRoundedRect(dotColorWidget->rect(), sizeDot/2, sizeDot/2);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    dotColorWidget->setMask(mask);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, COLORS[playerID+1]);

    dotColorWidget->setAutoFillBackground(true);
    dotColorWidget->setPalette(pal);

    lblName = new QLabel(namePlayer, this);
    lblScore = new QLabel("0", this);

    mainLayout->addWidget(dotColorWidget);
    mainLayout->addWidget(lblName);
    mainLayout->addWidget(lblScore);

    lblScore->setText(QString::number(score));
}


