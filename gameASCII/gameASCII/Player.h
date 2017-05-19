#pragma once

#include "Item.h"
#include <vector>

typedef vector<Item> Items;

class Player
{
public:
	Player();
	void init(int level, int health, int attack, float defense, int experience, int nxtLvlXP, int money);

	// ��������� ����
	int takeDamage(int attack);

	// ���� ����� ������
	void giveItem(Item item);

	// ���������� ������ ����� �� ����� ����
	int attack()const;

	// Upgrade item
	bool upgradeItem(Item & item);

	// Setters
	void setPosition(int x, int y);
	void addExperience(int experience);
	void addMoney(int money);

	// Getters
	void getPosition(int &x, int &y)const;
	int getLevel()const{ return _level; }
	int getHealth()const{ return _health; }
	int getMaxHealt()const{ return _maxHealth; }
	int getAttack()const;
	float getDefense()const;
	int getExperience()const{ return _experience; }
	int getXPProgress()const{ return (int)((_experience / _nextLevelXP) * 100); }
	int getNextLevelXP()const{ return _nextLevelXP; }
	int getMoney()const{ return _money; }
	bool isItem(int id)const;

private:
	// Characters
	int _level;
	int _health;
	int _maxHealth;
	int _attack;
	float _defense;
	int _experience;
	int _nextLevelXP;
	int _money;
	 
	// Position
	int _x;
	int _y;

public:
	Items _items;
};