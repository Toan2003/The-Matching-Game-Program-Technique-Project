#include "MatchingFunction.h"

int maxI(int x, int y)
{
	if (x < y)
	{
		x = y;
	}
	return x;
}

int minI(int x, int y)
{
	if (x > y)
	{
		x = y;
	}
	return x;
}

bool checkLineX(char **board, int x1, int x2, int y, int mode) 
{
	int xMin = minI(x1, x2);
	int xMax = maxI(x1, x2);
	for (int x = xMin + mode ; x <= xMax - mode ; x++)
	{
		if (board[x][y] != bond && board[x][y] != barrier )
		{
			return false;
		}
	}
	return true;
}

bool checkLineY(char **board, int y1, int y2, int x, int mode)
{
	int yMin = minI(y1, y2);
	int yMax = maxI(y1, y2);
	for (int y = yMin + mode; y <= yMax - mode; y++)
	{
		if (board[x][y] != bond && board[x][y] != barrier)
		{
			return false;
		}
	}
	return true;
}

bool iMatching(char **board, cell a, cell b)
{
	if (a.y == b.y)
	{
		return checkLineX(board, a.x, b.x, a.y, 1);
	}
	if (a.x == b.x)
	{
		return checkLineY(board, a.y, b.y, a.x, 1); 
	}
	return false;
}

bool zMatching(char** board, cell a, cell b)
{
	cell yMax, yMin, xMax, xMin;
	if (a.y < b.y)
	{
		yMax = b;
		yMin = a;
	}
	else
	{
		yMax = a;
		yMin = b;
	}
	if (a.x < b.x)
	{
		xMax = b;
		xMin = a;
	}
	else
	{
		xMax = a;
		xMin = b;
	}
	//y direction (horizontal)
	for (int y = yMin.y + 1; y < yMax.y; y++)
	{
		if (checkLineY(board, yMin.y + 1, y, yMin.x,0) && checkLineX(board, yMin.x, yMax.x, y,0) && checkLineY(board, y, yMax.y - 1, yMax.x,0))
		{
			return true;
		}
	}
	// x direction (vertical)
	for (int x = xMin.x + 1; x < xMax.x; x++)
	{
		if (checkLineX(board, xMin.x + 1, x, xMin.y,0) && checkLineY(board, xMin.y, xMax.y, x,0) && checkLineX(board, x, xMax.x - 1, xMax.y,0))
		{
			return true;
		}
	}
	return false;
}

bool lMatching(char** board, cell a, cell b)
{
	cell yMax, yMin;
	if (a.y < b.y)
	{
		yMax = b;
		yMin = a;
	}
	else
	{
		yMax = a;
		yMin = b;
	}

	// to right 
	if (checkLineY(board, yMin.y +1, yMax.y, yMin.x,0) && checkLineX(board, yMin.x, yMax.x ,yMax.y,1 )){
		return true;
	}
	//to left
	if (checkLineY(board, yMax.y -1, yMin.y, yMax.x, 0) && checkLineX(board, yMin.x, yMax.x, yMin.y, 1)) {
		return true;
	}
	return false;
}

bool checkMoreLineY(char** board, cell y1, cell y2, int mode, int column) {
	cell yMax, yMin;
	if (y1.y < y2.y)
	{
		yMax = y2;
		yMin = y1;
	}
	else
	{
		yMax = y1;
		yMin = y2;
	}
	int y = yMax.y + 1;
	int row = yMin.x;
	bool trungGian;
	if (mode == -1) { // mode -1 check to left of the board else to right
		y = yMin.y -1;
		row = yMax.x;
		trungGian = checkLineY(board, yMax.y, y, row, 1);
	}
	else {
		trungGian = checkLineY(board, yMin.y, y, row, 1);
	}
	if (trungGian) {
		while ((board[yMin.x][y] == bond || board[yMin.x][y] == barrier)
			&& (board[yMax.x][y] == bond || board[yMax.x][y] == barrier)
			&& (y >= 0 && y <= column)) {
			if (checkLineX(board, yMin.x, yMax.x, y, 1)) {
				return true;
			}
			y += mode;
		}
	}
	return false;
}

bool checkMoreLineX(char** board, cell x1, cell x2, int mode, int row) {
	cell xMax,xMin;
	if (x1.x < x2.x)
	{
		xMax = x2;
		xMin = x1;
	}
	else
	{
		xMax = x1;
		xMin = x2;
	}
	int x = xMax.x + 1;
	int col = xMin.y;
	bool trungGian;
	if (mode == -1) { // mode -1 check to top else to bottom
		x = xMin.x - 1;
		col = xMax.y;
		trungGian = checkLineX(board, xMax.x, x, col, 1);
	}
	else {
		trungGian = checkLineX(board, xMin.x, x, col, 1);
	}
	if (trungGian) {
		while ((board[x][xMin.y] == bond || board[x][xMin.y] == barrier)
			&& (board[x][xMax.y] == bond || board[x][xMax.y] == barrier)
			&& (x >= 0 && x <= row)) {
			if (checkLineY(board, xMin.y, xMax.y, x, 1)) {
				return true;
			}
			x += mode;
		}
	}
	return false;
}

bool uMatching(char** board, cell b, cell c, int column, int row) {
	if (checkMoreLineX(board, b, c, 1, row)) {
		return true;
	}
	if (checkMoreLineX(board, b, c, -1, row)) {
		return true;
	}
	if (checkMoreLineY(board, b, c, 1, column)) {
		return true;
	}
	if (checkMoreLineY(board, b, c, -1, column)) {
		return true;
	}
	return false;
}

bool isMatching(char** boardPokemon, cell a, cell b, int column, int row) {

	if (boardPokemon[a.x][a.y] != boardPokemon[b.x][b.y]) {
		return false;
	}
	if (a.x != b.x || a.y != b.y) {
	}
	else {
		return false;
	}
	// use four if to find bug easily
	if (iMatching(boardPokemon, a, b) ) {
		return true;
	}
	if (zMatching(boardPokemon, a, b)) {
		return true;
	}
	if (lMatching(boardPokemon, a, b) ) {
		return true;
	}
	if (uMatching(boardPokemon, a, b, column, row)) {
		return true;
	}
	return false;
}
