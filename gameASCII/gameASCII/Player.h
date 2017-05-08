#pragma once

#include "Item.h"
#include <vector>

typedef vector<Item> Items;

class Player
{
public:
	Player();
	void init(int level, int health, int attack, float defense, int experience, int money);

	int attack();

	int takeDamage(int attack);
	void giveItem(Item item);
	void reloadItem();

	// Upgrade item
	bool upgradeItem(Item & item);

	// Setters
	void setPosition(int x, int y);
	void addExperience(int experience);
	void addMoney(int money);
	void subMoney(int money);

	// Getters
	void getPosition(int &x, int &y)const;
	int getLevel()const{ return _level; }
	int getHealth()const{ return _health; }
	int getAttack()const{ return _attack; }
	float getDefense()const{ return _defense; }
	int getExperience()const{ return _experience; }
	int getXPProgress()const{ return (int)((_experience / _nextLevelXP) * 100); }
	int getNextLevelXP()const{ return _nextLevelXP; }
	int getMoney()const{ return _money; }
	int getMaxHealt()const{ return _maxHealth; }
	bool isItem(int id)const;
	bool isAlife()const;

private:
	// Properties
	int _level;
	int _health;
	int _maxHealth;
	int _attack;
	int _baseAttack;
	float _defense;
	int _experience;
	int _nextLevelXP = 50;
	int _money;
	 
	// Position
	int _x;
	int _y;

public:
	Items _items;
};