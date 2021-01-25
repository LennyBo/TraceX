#include "keyIcon.h"
#include "constants.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QMap>

#include <QDebug>

KeyIcon::KeyIcon(int keyIndex, QWidget *parent) : QWidget(parent)
{
    lblKey2 = new QLabel(KEYS[keyIndex].keySymbolLeft, this);
    lblKey1 = new QLabel(KEYS[keyIndex].keySymbolRight, this);

    lblKey1->setStyleSheet("border: 1px solid black; padding: 3 3 3 3");
    lblKey1->setAlignment(Qt::AlignCenter);

    lblKey2->setStyleSheet("border: 1px solid black; padding: 3 3 3 3;");
    lblKey2->setAlignment(Qt::AlignCenter);

    layout = new QHBoxLayout(this);
    layout->addWidget(lblKey1);
    layout->addWidget(lblKey2);
}
