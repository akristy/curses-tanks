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
	
	


	int col;
	int row;
    
	double power;
	double angle;
	int health;
	Side s;
    bool hit;

	static const int power_increment;
	static const double angle_increment;
};
