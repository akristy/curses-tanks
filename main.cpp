#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

#if defined(_WIN32)
#include <Windows.h>
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#include <unistd.h>
#endif

#include "ground.hpp"
#include "player.hpp"

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const double PI = 3.141592653589793238463;

void MySleep(int milliseconds)
{
#if defined(WIN32)
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}
void DrawScreen(Ground & g, Player * players, int turn)
{
	erase();
	box(stdscr, 0, 0);
	players[0].Draw(g);
	players[1].Draw(g);
	g.Draw();
	players[0].DrawSettings(turn);
	players[1].DrawSettings(turn);
	refresh();
}

//http://www.iforce2d.net/b2dtut/projected-trajectory

void Shoot(Ground & g, Player * players, int turn)
{
	double angle = players[turn].angle / 180.0 * PI;
	double y_component = sin(angle) * players[turn].power * 0.2;
	double x_component = cos(angle) * players[turn].power * 0.2;

	double pNx; //position of astrics  x = columns
	double pNy; //position of astrics  y = lines
	double time_divisor = 15.0;

	if (players[turn].s == RIGHT)
		x_component = -x_component;

	double p0x = players[turn].col;
	double p0y = g.ground.at(players[turn].col);
	// higher ground numbers are lower altitudes (0 is first line, etc).
	p0y = LINES - p0y;
	for (int i = 1; i < 5000; i++)
	{
		double di = i / time_divisor;

		pNx = (int)(p0x + di * x_component);
		pNy = p0y + di * y_component + (di * di + di) * -9.8 / time_divisor / 1.5;
		pNy = (int)(LINES - pNy); //where the y gets flipped
		if (pNx < 1 || pNx >= COLS - 2)
			break;
		if (pNy < 1) {
			MySleep(30);
			continue;
		}
		//	if (pNy >= LINES - 2)
		//		break;
		move((int)pNy - 1, (int)pNx + 1);
		addch('*');
		
		if (pNy > g.ground.at((int)pNx))
			break;
		bool hit = false;
		if ((pNy >= g.ground.at(players[1 - turn].col -1) && pNy <= g.ground.at(players[1 - turn].col + 1)) 
			&& (pNx >= players[1 - turn].col - 1 && pNx <= players[1 - turn].col + 1))
		{
			players[1 - turn].health -= 10;
			hit = true;
			g.ground.clear();
			g.InitializeGround();
		}
		else if ((pNy >= g.ground.at(players[turn].col - 1) && pNy <= g.ground.at(players[turn].col + 1))
			&& (pNx >= players[turn].col - 1 && pNx <= players[turn].col + 1))
		{
			players[turn].health -= 10;
			hit = true;
		}
		
		refresh();
		MySleep(30);
		
		if (hit)
		{
			break;
		}
	}
}

int main(int argc, char * argv[])
{
	srand((unsigned int)time(nullptr));

	int turn = 0;
	bool keep_going = true;
	Ground g;
	Player players[2];
	Player new_players[2];

	initscr();
	noecho();
	keypad(stdscr, 1);

	g.InitializeGround();
	players[0].Initialize(rand() % (COLS / 4), LEFT);
	players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);

	DrawScreen(g, players, turn);
	while (keep_going)
	{
		bool show_char = false;
		int c = getch();
		switch (c)
		{
		case 27:
			keep_going = false;
			break;
        case 'a':
		case 260:
			players[turn].PowerDown();
			break;
        case 'd':
		case 261:
			players[turn].PowerUp();
			break;
        case 'w':
		case 259:
			players[turn].AngleUp();
			break;
        case 's':
		case 258:
			players[turn].AngleDown();
			break;

		case 10:
		case KEY_ENTER:
#if defined(WIN32)
		case PADENTER:
#endif
			Shoot(g, players, turn);
			turn = 1 - turn;
			if (turn < 0 || turn > 1) {
				turn = 1;
			}
			break;

		default:
			show_char = true;
			break;
		}
		if (players[turn].health == 0 || players[1 - turn].health == 0)
		{
			erase();
			box(stdscr, 0, 0);
			move(LINES/2, COLS/2 - 7);
			addstr("Game Over!!!!!");
			move(LINES / 2 + 2, COLS / 2 - 7);
			addstr("Continue? (y/n)");
			int c = getch();
			switch (c)
			{
			case 'y':
				keep_going = true;
				
				new_players[0].Initialize(rand() % (COLS / 4), LEFT);
				new_players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);
				players[0] = new_players[0];
				players[1] = new_players[1];
				turn = 0;
				DrawScreen(g, players, turn);				
				break;
			case 'n':
				erase();
				addstr("Hit any key to exit");
				refresh();
				getch();
				echo();
				endwin();
				return 0;
				break;
			}

			refresh();
			MySleep(30);

		}
		else
		{
			DrawScreen(g, players, turn);
		}
		if (show_char) {
			move(0, 1);
			stringstream ss;
			ss << setw(4) << c << " ";
			addstr(ss.str().c_str());
			refresh();
		}
	}
	/*erase();
	addstr("Hit any key to exit");
	refresh();*/
	getch();
	echo();
	endwin();
	return 0;
}
