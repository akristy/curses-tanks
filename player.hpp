#pragma once
#include "ground.hpp"

enum Side
{
	LEFT,
	RIGHT
};

class Player
{
public:
	Player();
	void Draw(Ground & ground);
	void Initialize(int column, Side side);
	void DrawSettings(int turn);
	void PowerUp();
	void PowerDown();
	void AngleUp();
	void AngleDown();
	bool Hit(int shotPosX, int shotPosY, Player & other); //tank positions
	
	


	int col;
	int row;
	int Shotcol; //column position of shot
	int Shotline; // line position of shot
	double power;
	double angle;
	int health;
	int new_health;
	Side s;

	static const int power_increment;
	static const double angle_increment;
};
