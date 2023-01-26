#include "Board.h"
#include "MatchingFunction.h"

void setColor(int backgound_color, int text_color) 
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void goTo(short posX, short posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void board::initialize() {
	row = 8;
	column = 8;
	type = 11;
	int trunggian[11] = { 4,4,2,6,4,4,4,2,2,2,2 };
	countType = new int[type];
	for (int i = 0; i < 11; i++) {
		countType[i] = trunggian[i];
	}
}

void board::generateBoard()
{
	// generete board with pointer (dynamic allocation)
	boardPokemon = new char *[row];
	for (int i = 0; i < row; i++)
	{
		boardPokemon[i] = new char[column];
	}
	// set value for cells which are barrier
	srand(int(time(NULL)));
	for (int i = 0; i < column; i++)
	{
		boardPokemon[0][i] = barrier;
		boardPokemon[row - 1][i] = barrier;
	}
	for (int i = 0; i < row; i++)
	{
		boardPokemon[i][0] = barrier;
		boardPokemon[i][column - 1] = barrier;
	}
	// set value for cells in board

	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			do
			{
				boardPokemon[i][j] = rand() % type + 65; // 0->type -1 + 65 means value run from A to A + type-1
			} while (countType[boardPokemon[i][j] - 65] == 0); //check if the characters has appeared more than its was defined, if yes random again until it's recieve the valid character
			countType[boardPokemon[i][j] - 65]--; 
		}
	}

	return;
}

bool board::checkEndGame()
{
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			if (boardPokemon[i][j] != bond)
			{
				return false;
			}
		}
	}
	return true;
}

bool board::checkValidPair()
{
	int** a = new int* [type];
	for (int i = 0; i < type; i++) { 
		a[i] = new int[10]; // no type of characters can appear more than 10 (based on countType array)
	}
	// the 2 dimension array store the positions of each type of character 

	for (short i = 1; i < row - 1; i++)
	{
		for (short j = 1; j < column - 1; j++)
		{
			if (boardPokemon[i][j] == bond) continue;
			++countType[boardPokemon[i][j] - 65]; //count the appearances of each character and save its position to the below array
			a[boardPokemon[i][j] - 65][countType[boardPokemon[i][j] - 65]] = (i * 10) + j; //save position, x means (row) and j means y (column)
		}
	}
	cell b, c;
	for (int i = 0; i < type; i++) {
		for (int j = 1; j < countType[i]; j++) {
			b.x = a[i][j] / 10;
			b.y = a[i][j] % 10;
			for (int k = j + 1; k <= countType[i]; k++) {
				c.x = a[i][k] / 10;
				c.y = a[i][k] % 10;
				if (isMatching(boardPokemon, b, c, column, row)) {
					for (int i = 0; i < type; i++) {
						countType[i] = 0;
						delete[] a[i];
					}
					delete[] a;
					return true;
				}
			}
		}
	}
	for (int i = 0; i < type; i++) {
		countType[i] = 0;
		delete [] a[i];
	}
	delete [] a;
	return false;
}

void board::moveSuggestion(cell& a1, cell& a2, int count) { //based on checkValidPair function
	int** a = new int* [type];
	for (int i = 0; i < type; i++) {
		a[i] = new int[10]; 
	}
	for (short i = 1; i < row - 1; i++)
	{
		for (short j = 1; j < column - 1; j++)
		{
			if (boardPokemon[i][j] == bond) continue;
			++countType[boardPokemon[i][j] - 65]; 
			a[boardPokemon[i][j] - 65][countType[boardPokemon[i][j] - 65]] = (i * 10) + j; 
		}
	}
	cell b, c;
	for (int i = 0; i < type; i++) {
		for (int j = 1; j < countType[i]; j++) {
			b.x = a[i][j] / 10;
			b.y = a[i][j] % 10;
			for (int k = j + 1; k <= countType[i]; k++) {
				c.x = a[i][k] / 10;
				c.y = a[i][k] % 10;
				if (isMatching(boardPokemon, b, c, column, row)) {
					a1 = b;
					a2 = c;
					count = 0;
					for (int i = 0; i < type; i++) {
						countType[i] = 0;
						delete[] a[i];
					}
					delete[] a;
					return;
				}
			}
		}
	}
	for (int i = 0; i < type; i++) {
		countType[i] = 0;
		delete[] a[i];
	}
	delete[] a;
	return;
}

void board::drawBoard(cell a, cell b)
{
	goTo(0, 0);
	cout << endl << endl;
	for (int i = 1; i < row - 1; i++)
	{
		if (i == 1)
		{
			cout << "           ";
			for (int j = 1; j < column - 1; j++)
			{
				if (boardPokemon[i][j] == bond)
				{
					cout << "         ";
					continue;
				}
				cout << " ------- ";
			}
		}
		cout << endl;
		cout << "           ";
		for (int j = 1; j < column - 1; j++)
		{
			if (boardPokemon[i][j] == bond)
			{
				if (a.x == i)
				{
					if (a.y == j)
					{
						cout << " ";
						setColor(7, 7);
						cout << "       ";
						setColor(0, 7);
						cout << " ";
						continue;
					}
				}
				if (b.x == i)
				{
					if (b.y == j)
					{
						cout << " ";
						setColor(7, 7);
						cout << "       ";
						setColor(0, 7);
						cout << " ";
						continue;
					}
				}
				cout << "         ";
				continue;
			}
			if (a.x == i)
			{
				if (a.y == j)
				{
					cout << "|";
					setColor(7, 4);
					cout << "       ";
					setColor(0, 7);
					cout << "|";
					continue;
				}
			}
			if (b.x == i)
			{
				if (b.y == j)
				{
					cout << "|";
					setColor(7, 4);
					cout << "       ";
					setColor(0, 7);
					cout << "|";
					continue;
				}
			}
			cout << "|       |";
		}

		cout << endl;
		cout << "           ";
		for (int j = 1; j < column - 1; j++)
		{
			if (boardPokemon[i][j] == bond)
			{
				if (a.x == i)
				{
					if (a.y == j)
					{
						cout << " ";
						setColor(7, 7);
						cout << "       ";
						setColor(0, 7);
						cout << " ";
						continue;
					}
				}
				if (b.x == i)
				{
					if (b.y == j)
					{
						cout << " ";
						setColor(7, 7);
						cout << "       ";
						setColor(0, 7);
						cout << " ";
						continue;
					}
				}
				cout << "         ";
				continue;
			}
			if (a.x == i)
			{
				if (a.y == j)
				{
					cout << "|";
					setColor(7, 4);
					cout << "   " << boardPokemon[i][j] << "   ";
					setColor(0, 7);
					cout << "|";
					continue;
				}
			}
			if (b.x == i)
			{
				if (b.y == j)
				{
					cout << "|";
					setColor(7, 4);
					cout << "   " << boardPokemon[i][j] << "   ";
					setColor(0, 7);
					cout << "|";
					continue;
				}
			}
			cout << "|   " << boardPokemon[i][j] << "   |";
		}

		cout << endl;
		cout << "           ";
		for (int j = 1; j < column - 1; j++)
		{
			if (boardPokemon[i][j] == bond)
			{
				if (a.x == i)
				{
					if (a.y == j)
					{
						cout << " ";
						setColor(7, 7);
						cout << "       ";
						setColor(0, 7);
						cout << " ";
						continue;
					}
				}
				if (b.x == i)
				{
					if (b.y == j)
					{
						cout << " ";
						setColor(7, 7);
						cout << "       ";
						setColor(0, 7);
						cout << " ";
						continue;
					}
				}
				cout << "         ";
				continue;
			}
			if (a.x == i)
			{
				if (a.y == j)
				{
					cout << "|";
					setColor(7, 4);
					cout << "       ";
					setColor(0, 7);
					cout << "|";
					continue;
				}
			}
			if (b.x == i)
			{
				if (b.y == j)
				{
					cout << "|";
					setColor(7, 4);
					cout << "       ";
					setColor(0, 7);
					cout << "|";
					continue;
				}
			}
			cout << "|       |";
		}
		cout << endl;
		cout << "           ";
		for (int j = 1; j < column - 1; j++)
		{
			if (boardPokemon[i][j] == bond)
			{
				if (boardPokemon[i + 1][j] == bond || boardPokemon[i + 1][j] == barrier)
				{
					cout << "         ";
					continue;
				}
			}
			cout << " ------- ";
		}
	}
}

void board::deleteBoard()
{
	for (int i = 0; i < row; i++)
	{
		delete[] boardPokemon[i];
	}
	delete[] boardPokemon;
	delete[] countType;
	return;
}

void leaderBoard(bool mode, int time) {
	short n;
	ifstream ac("leaderBoard.txt"); 
	ac >> n;
	ac.ignore();
	if (mode) { //show information
		system("cls");
		cout << endl << endl << endl;
		cout << "        Rank:  Name:" << endl;
		if (n == 0) {
			system("pause");
			ac.close();
			return;
		}
		Player s[5];
		for (int i = 0; i < n; i++) {
			getline(ac, s[i].name, '/');
			ac >> s[i].time;
			ac.ignore();
			cout << "         " << i+1 << "     " << s[i].name << "  Time:" << s[i].time << " seconds" << endl << endl;
		}
		ac.close();
		system("pause");
		system("cls");
	} else { // store information
		Player person;
		cout << endl << endl << endl;
		cout << "           Enter Your Name: ";
		getline(cin, person.name);
		person.time = time;
		Player s[5];
		for (int i = 0; i < n; i++) {
			getline(ac, s[i].name, '/');
			ac >> s[i].time;
			ac.ignore();
		}
		for (int i = 0; i < n; i++) {
			if (s[i].time > person.time) {
				swap(s[i], person);
			}
		}
		if (n < 5) {
			n++;
			s[n-1] = person;
		}
		ac.close();
		ofstream in("leaderBoard.txt");
		in << n << endl;
		for (int i = 0; i < n; i++) {
			in << s[i].name << '/' << s[i].time << endl;
		}
		in.close();
		leaderBoard(1, time);
	}

	return;
}

void board::difficultMode() {
	for (int a = 0; a < 2; a++) {
		for (int i = 1; i < row - 1; i++) {
			for (int j = 1; j < column - 1; j++) {
				if (boardPokemon[i][j] == bond) {
					for (int k = j; k < column - 2; k++) {
						boardPokemon[i][k] = boardPokemon[i][k + 1];
					}
					boardPokemon[i][column - 2] = bond;
				}
			}
		}
	}
	return;
}

void drawMenu(short n, bool mode) {
	goTo(0, 0);
	cout << endl << endl << endl;         
	cout << "                        PIKACHU VERSION CHARACTER REMAKE" << endl;
	cout << "      Use W,A,S,D or Arrow keys to move and use Space or Enter to select  " << endl;
	cout << "                        Pres Esc to exit, and h for help                  " << endl;
	cout << "                        ";//24
	if (n == 6) {
		goTo(24, n);
		setColor(9, 4);
	cout << "           Play Game           " << endl;
		setColor(0, 7);
	} else {
	cout << "           Play Game           " << endl;

	}

	cout << "                        ";
	if (n == 7) {
		goTo(24, n);
		setColor(9, 4);
		if (mode) {
	cout << "         Mode: Difficult       " << endl;
		}                   
		else {
	cout << "          Mode: Normal         " << endl;
		}
		setColor(0, 7);
	}
	else {
		if (mode) {
	cout << "         Mode: Difficult       " << endl;
		}
		else {
	cout << "          Mode: Normal         " << endl;
		}
	}

	cout << "                        ";
	if (n == 8) {
		goTo(24, n);
		setColor(9, 4);
	cout << "          Leader Board         " << endl;
		setColor(0, 7);

	}
	else {
	cout << "          Leader Board         " << endl;

	}


}

void menu(bool &mode, char& x) {
	short n = 6;
	drawMenu(n,mode);
	do {
		x = _getch();
		switch (x) {
			case 80: case 115: {//down
				n = n + 1;
				if (n > 8) n = 6;
				break;
			}
			case 72: case 119: {//up
				n = n -1;
				if (n < 6) n = 8;
				break;
			}
			case 32: case 13: {
				if (n == 7) {
					mode = !mode;
				}
				if (n == 6) {
					return;
				}
				if (n == 8) {
					leaderBoard(1, 0);
					//leaderBoard();
				}
			}
		}
		drawMenu(n, mode);
	} while (x != 27);
	return;
}