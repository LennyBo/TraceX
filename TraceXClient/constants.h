#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>
#include <QMap>

const int NUMBER_COLORS = 8;

const int PLAYER_WIDTH = 5;

const QColor COLORS[] = {Qt::white, Qt::red,Qt::green,Qt::blue,Qt::yellow,Qt::magenta,Qt::cyan,Qt::gray,Qt::white};
struct keyTest
{
    int keyValRight;
    QString keySymbolRight;
    int keyValLeft;
    QString keySymbolLeft;
};

const int MAX_LOCAL_PLAYERS = 3;
const keyTest KEYS[MAX_LOCAL_PLAYERS] =
{
    {.keyValRight = Qt::Key_A,.keySymbolRight="A",.keyValLeft=Qt::Key_D,.keySymbolLeft="D"},
    {.keyValRight = Qt::Key_Left,.keySymbolRight="<",.keyValLeft=Qt::Key_Right,.keySymbolLeft=">"},
    {.keyValRight = Qt::Key_J,.keySymbolRight="J",.keyValLeft=Qt::Key_L,.keySymbolLeft="L"}
};

const int GAME_SIZE = 800;
const int MARGIN_GRAPHICSVIEW = 20;

const int TIME_TO_SEND_DIRECTION = 62;

struct player
{
    QString name;
    int score;
    int colorID;
};

#endif // CONSTANTS_H
