#pragma once
#include "Board.h"


int maxI(int x, int y);
int minI(int x, int y);

bool checkLineX(char** board, int x1, int x2, int y, int mode);
bool checkLineY(char** board, int y1, int y2, int x, int mode);

bool checkMoreLineY(char** board, cell y1, cell y2, int mode, int column);
bool checkMoreLineX(char** board, cell x1, cell x2, int mode, int row);

bool iMatching(char** board, cell a, cell b);
bool zMatching(char** board, cell a, cell b);
bool lMatching(char** board, cell a, cell b);
bool uMatching(char** board, cell b, cell c, int column, int row);
bool isMatching(char** boardPokemon, cell a, cell b, int column, int row);

