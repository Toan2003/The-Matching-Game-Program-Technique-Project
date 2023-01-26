#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h> //goto and rezie and set color functions
#include <string>
#include <conio.h>//_getch function
#include <stdlib.h> //random funtion
#include <time.h> //time function an random function
using namespace std;

static char barrier = 1;
static char bond = 2;

struct cell { // the position of cell in board with x is its row and y is its column
	int x;
	int y;
};

struct board {
	int row; //will be 8 but real row just 6
	int column ; // will be 8 but real column just 6
	int type ; //types of character will appear (start from A)
	int *countType; //store the numbers of appearances of each character (in this case A will appear 4 times, B 4 times,..)
	char** boardPokemon;
	void initialize(); //generate value for row,column,type,countType
	void generateBoard();
	void drawBoard(cell a, cell b);
	void deleteBoard();
	bool checkEndGame();
	bool checkValidPair();
	void difficultMode();
	void moveSuggestion(cell& a1, cell& a2, int count);
};

struct Player { // to store information of players if they win for leaderBoard function
	string name;
	int time;
};

void setColor(int backgound_color, int text_color);
void goTo(short posX, short posY);
void resizeConsole(int width, int height);
void leaderBoard(bool mode, int time);
void menu(bool& mode, char &x);