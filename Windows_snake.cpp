#include <iostream>
#include <conio.h>
using namespace std;

bool game_over;
int width, height, x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir, prev_dir;
int ch;
void setup(int, int);
void draw();
void input();
void logic();
void won() { game_over = true; cout << "           /^\\/^\\                                      \n         _|_o| o|                                       \n\\/     /~     \\_/ \\                                    \n \\____|__________/  \\                                  \n        \\_______      \\                                \n                `\\     \\                   \\             \n                  |     |                   \\           \n                 /      /                    \\         \n                /     /                       \\\\       \n              /      /        <YOU WON!>       \\ \\     \n             /     /                            \\  \\   \n           /     /             _----_            \\   \\ \n          /     /           _-~      ~-_         |   | \n         (      (        _-~    _--_    ~-_     _/   | \n          \\     `~-____-~    _-~   `~-_   `~-_-~    /  \n           `~-_           _-~'         ~-_       _-~'  \n               ~--______-~                ~-___-~      \n"; }

void setup(int A, int B)
{
	width = A;
	height = B;
	game_over = false;
	dir = STOP;
	x = width / 2 + 1;
	y = height / 2 + 1;
	fruitX = rand() % (width - 1) + 1;
	fruitY = rand() % (height - 1) + 1;
	score = 0;
	tailX[0] = x;
	tailY[0] = y;
	tailX[1] = x;
	tailY[1] = y + 1;
	tailX[2] = x;
	tailY[2] = y + 2;
	nTail = 3;
}

void draw()
{
	system("cls");
	cout << "Score: " << score << "\n";

	for (int i = 1; i <= width + 2; ++i)
	{
		if (game_over && x == i - 2 && y == -1)
			cout << "X";
		else
			cout << "#";
	}
	cout << "\n";

	for (int i = 0; i <= height; ++i)
	{
		for (int j = -1; j <= width; ++j)
		{
			if (game_over && j == x && i == y)
				cout << "X";
			else if (j == -1 || j == width)
				cout << "#";
			else if (j == fruitX && i == fruitY)
				cout << "*";
			else if (j == x && i == y)
				cout << "O";
			else
			{
				bool istail = false;
				for (int k = 0; k < nTail; ++k) if (tailX[k] == j && tailY[k] == i) istail = true;
				if (istail) cout << "o";
				else cout << " ";
			}
		}
		cout << "\n";
	}

	for (int i = 1; i <= width + 2; ++i)
	{
		if (game_over && x == i - 2 && y == height + 1)
			cout << "X";
		else
			cout << "#";
	}
	cout << "\n";
	if (game_over) cout << "GAME OVER!\n";
}

void input() {

	ch = _getch();
	if (ch == 'a') { dir = (prev_dir == RIGHT) ? STOP : LEFT; prev_dir = dir; }
	else if (ch == 'd') { dir = (prev_dir == LEFT) ? STOP : RIGHT; prev_dir = dir; }
	else if (ch == 'w') { dir = (prev_dir == DOWN) ? STOP : UP; prev_dir = dir; }
	else if (ch == 's') { dir = (prev_dir == UP) ? STOP : DOWN; prev_dir = dir; }
	else if (ch == 'x') game_over = true;
	else dir = STOP;
	if (game_over) draw();
	if (dir != STOP) logic();
}

void logic()
{
	if (dir == LEFT)--x;
	else if (dir == RIGHT)++x;
	else if (dir == UP)--y;
	else if (dir == DOWN)++y;
	dir = STOP;
	if (x == fruitX && y == fruitY)
	{
		++score;
		if (score == (width*height) / 2) won();
		++nTail;
		tailX[nTail] = tailX[nTail - 1];
		tailY[nTail] = tailY[nTail - 1];
		fruitX = rand() % (width - 1) + 1;
		fruitY = rand() % (height - 1) + 1;
	}
	for (int i = nTail; i >= 0; --i) { tailX[i + 1] = tailX[i]; tailY[i + 1] = tailY[i]; }
	tailX[0] = x;
	tailY[0] = y;
	if (x < 0 || x >= width || y<0 || y>height) { game_over = true; draw(); }
	for (int i = 1; i < nTail; ++i) { if (tailX[i] == x && tailY[i] == y) { game_over = true; draw(); break; } }
}


int main()
{
	cout << "Welcome to Snake Game!    ____\n ________________________/ O  \\___/\n{_O_O_O_O_O_O_O_O_O_O_O_O_____/   \\\nPress Enter to START.\n";
	cin.ignore();
	int A = 100, B = 25;
	cout << "Use WASD To Move.\nEnter The Width And The Height Of The Playing Area: ";
	cin >> A >> B;
	setup(A, B);
	while (!game_over)
	{
		draw();
		input();
	}
	cout << "Press Enter to Exit\n";
	cin.ignore();
	return 0;
}
