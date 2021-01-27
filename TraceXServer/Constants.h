#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>

//Server constants
const int DEFAULT_PORT = 8080;

//Manager constants
const int TIME_TO_TICK = 62; //Ms
const int TIME_TO_SCORE_UPDATE = 333; //Ms
//const type NB_OF_TICKS_TO_UPDATE (int) (TIME_TO_SCORE_UPDATE/TIME_TO_TICK)
const int MAX_PLAYER_COUNT = 8;
const int DELAY_BETWEEN_ROUND = 2000; //Ms

//Player constants
const int PLAYER_WIDTH = 5;
const int DEFAULT_SPEED = 5;
const bool DEFAULT_ALIVE = true;
const bool DEFAULT_READY = false;
const int TURN_RATE = 10;       //Degrees per tick
const int MARGIN_COLLIDE = 5;
const QColor COLORS[] = {Qt::red,Qt::green,Qt::blue,Qt::yellow,Qt::magenta,Qt::cyan,Qt::gray,Qt::white};
const double SCORE_PER_TICK = 0.082;
const int ROUND_WIN_BONUS = 15;

//Size in pixels of the scene we are using
const int GAME_SIZE = 800;
const int SPAWN_AREA = 400;
const int SPAWN_AREA_PADDING = ((GAME_SIZE - SPAWN_AREA)/2);
const int MARGIN_GRAPHICSVIEW = 20;

#endif // CONSTANTS_H
