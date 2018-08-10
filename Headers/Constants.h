#pragma once
enum PointType { EMPTY_FIELD, PLAYER_FIGURE, BORDER, BLOCK };

const int GAME_FIELD_HEIGHT = 20;
const int GAME_FIELD_WIDTH = 17;
const int TETRIS_FIELD = 15;
const int FIGURE_COUNT = 7;
const int POINTS_MAX = 4;
const int SQUARE = 6;
const int Figures[FIGURE_COUNT][POINTS_MAX] =
{ 1, 3, 5, 7,
  2, 4, 5, 7 ,
  3, 5, 4, 6 ,
  3, 5, 4, 7 ,
  2, 3, 5, 7 ,
  3, 5, 7, 6 ,
  2, 3, 4, 5  };
//const int BUTTON_UP = 38;
const int BUTTON_DOWN = 80;
const int BUTTON_LEFT = 75;
const int BUTTON_RIGHT =77;
const int SPACE = 32;
const float MAX_DELAY = 0.5;