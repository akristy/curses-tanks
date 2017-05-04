#include <sstream>
#include <iomanip>
#include "player.hpp"

#if defined(_WIN32)
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#endif

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const int Player::power_increment = 1;
const double Player::angle_increment = 1;

Player::Player()
{
	s = LEFT;
	col = 0;
	angle = 45.0;
	power = 50.0;
	health = 30;
    bool hit = false;
}

void Player::Initialize(int column, Side side)
{
	col = column;
	s = side;
}

void Player::Draw(Ground & g)
{
	mvaddch(g.ground.at(col) - 1, col + 1, '@'); //col is left or right while g.ground is up and down
	
}

bool Player::Hit(int shotPosX, int shotPosY, Player & other, Ground & g)  //playerline and playercolumn are positions for tank
{
    
    int other_tank_line = g.ground.at(other.col) - 1;
    int other_tank_col = other.col + 1;
   
    
	bool registered = true;
    

    
    if((other_tank_line + 1 <= shotPosX && shotPosX >= other_tank_line -1 ) && ( other_tank_col  - 1 >= shotPosY && other_tank_col + 1  <= shotPosY))
    {
        
		//do not return before an instruction!
		other.health -= 10;
		
    }
    else
    {
		registered = false; // it does not hit
		
    }
	return registered;
}






void Player::PowerUp()
{
	power += power_increment;
    if (power >=80)
        power = 80;
}

void Player::PowerDown()
{
	power -= power_increment;
	if (power <= 0)
		power = power_increment;
}

void Player::AngleUp()
{
	angle += angle_increment;
	if (angle >= 90.0)
		angle = 90.0;
}

void Player::AngleDown()
{
	angle -= angle_increment;
	if (angle < 0.0)
		angle = 0.0;
}

void Player::DrawSettings(int turn)
{
	bool my_turn = (turn == 0 && s == LEFT) || (turn == 1 && s == RIGHT);

	int starting_column = 2;
	int line = 1;
	char player = (s == LEFT) ? '1' : '2';
	stringstream ss;

	if (s == RIGHT)
		starting_column = COLS - 18;

	if (my_turn)
		attron(A_STANDOUT);
	ss << setw(10) << left << "Player:" << player;
	mvaddstr(line++, starting_column, ss.str().c_str());
	if (my_turn)
		attroff(A_STANDOUT);

	ss = stringstream();
	ss << setw(10) << left << "Angle: " << setw(6) << angle;
	mvaddstr(line++, starting_column, ss.str().c_str());
	
	ss = stringstream();
	ss << setw(10) << left << "Power: " << setw(6) << power;
	mvaddstr(line++, starting_column, ss.str().c_str());

	ss = stringstream();
	ss << setw(10) << left << "Health: " << setw(6) << health;
	mvaddstr(line++, starting_column, ss.str().c_str());
}
