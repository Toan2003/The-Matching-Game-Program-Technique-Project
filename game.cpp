#include "Board.h"
#include "MatchingFunction.h"
//#pragma comment (lib, "winmm.lib") to play sound

int main()
{
	resizeConsole(590, 600);
	bool mode = false; // 0 for normal mode and 1 for difficult mode
	char x =28;
	menu(mode,x);
	if (x == 27) return -1;
	system("cls");
	board game;
	game.initialize();
	cell a = { 1,1 }; 
	cell b = { 0,0 };
	int count = 0; 
	game.generateBoard();
	time_t begin = time(NULL);
	while (x!= 27) {
		game.drawBoard(a, b);
		if (game.checkEndGame()) break;
		if (!game.checkValidPair()) { // no valid pair left means player lost and their name do not be writen to leaderBoard
			cout << endl << "    -------> No Valid Pair left" << endl;
			//PlaySound(TEXT("SkyFall.wav"), NULL, SND_FILENAME | SND_ASYNC); //play sound but only available when you use visual studio in windows
			system("pause");
			system("cls");
			cout << endl << endl << endl << endl << "              ";
			setColor(7, 4);
			cout << "                     LOSER!!                      ";
			setColor(0, 7);
			cout << endl << endl;
			game.deleteBoard();
			system("pause");
			return 1;
		}
		x = _getch();
		switch (x) { // move in game
			case 104: {
				game.moveSuggestion(a, b, count);
				break;
			}
			case 80: case 115: {//down
				if (count == 1) {
					b.x = b.x % (game.row - 2) + 1;
					break;
				}
				a.x = a.x % (game.row - 2) + 1;
				break;
			}
			case 72: case 119: {//up
				if (count == 1) {
					b.x = (b.x + game.row -4)  % (game.row- 2) +1;
					break;
				}
				a.x = (a.x + game.row - 4) % (game.row-2) +1;
				break;
			}
			case 77: case 100: {//right
				if (count == 1) {
					b.y = b.y % (game.column - 2) + 1;
					break;
				}
				a.y = a.y % (game.column - 2) + 1;
				break;
			}
			case 75: case 97: {//left
				if (count == 1) {
					b.y = (b.y + game.column - 4) % (game.column - 2) + 1;
					break;
				}
				a.y = (a.y + game.column - 4) % (game.column - 2) + 1;
				break;
			}
			case 13: case 32: {//enter or space
				if (count == 1 ) {
					if (isMatching(game.boardPokemon,a,b,game.column, game.row)) {
						game.boardPokemon[a.x][a.y] = bond;
						game.boardPokemon[b.x][b.y] = bond;
						a = b;
						b.x = 0;
						b.y = 0;
					} else {
						a = b;
						b.x = 0;
						b.y = 0;
					}
					count = 0;
					break;
				}
				b = a;
				count++;
				break;
			}
		}
		if (mode) {
			game.difficultMode();
		}
	}
	if (x == 27) return -1;
	time_t end = time(NULL);
	int second = difftime(end, begin); //time point of player
	//PlaySound(TEXT("chienthang.wav"), NULL, SND_FILENAME | SND_ASYNC);
	leaderBoard(0, second);
	game.deleteBoard();
	return 0;
}

