#pragma once

#include <iostream>
#include <stack>
#include "global.h"

using namespace std;

class Enemy
{
public:
	Enemy(string name, char tile, int level, int attack, float defense, int health, int money);

	// ¬озвращает размер урона от атаки моба
	int attack()const;

	// ¬озвращает размер денежного вознаграждени€ за убийство моба
	int getReward()const;

	// ѕринимаем удар
	int takeDamage(int attack);

	// Setters
	void setPosition(int x, int y);

	// Getters
	void getPosition(int &x, int &y)const;
	string getName()const{ return _name; }
	char getTile()const{ return _tile; }

	// Gets AI move command
	char getMove(int playerX, int playerY);

private:
	// Characters
	string _name;
	char _tile;

	// 
	int _level;
	int _health;
	int _maxHealth;
	int _attack;
	float _defense;
	int _money;

	// Route
	stack<char> route;

	//Position
	int _x;
	int _y;
};