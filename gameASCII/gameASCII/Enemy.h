#pragma once

#include <iostream>
#include <stack>
#include "global.h"

using namespace std;

class Enemy
{
public:
	Enemy(string name, char tile, int level, int attack, float defense, int health, int money, COORD p);

	// ���������� ������ ����� �� ����� ����
	int attack()const;

	// ���������� ������ ��������� �������������� �� �������� ����
	int getReward()const;

	// ��������� ����
	int takeDamage(int attack);

	// Setters
	void setPosition(COORD coord);

	// Getters
	COORD getPosition()const;
	string getName()const;
	char getTile()const;

	// Gets AI move command
	char getMove(COORD playerCoord);

private:
	// Characters
	string m_name;
	char m_tile;

	// 
	int m_level;
	int m_health;
	int m_maxHealth;
	int m_attack;
	float m_defense;
	int m_money;

	// Route
	stack<char> route;

	//Position
	COORD m_coord;
};