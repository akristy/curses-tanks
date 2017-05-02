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
	bool Hit(int playerline, int playercol); //tank positions

	int col;
	int Shotcol; //column position of shot
	int Shotline; // line position of shot
	double power;
	double angle;
	double health = 30;
	Side s;

	static const int power_increment;
	static const double angle_increment;
};
