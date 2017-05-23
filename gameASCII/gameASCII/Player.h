#pragma once

#include "Item.h"
#include "global.h"
#include <vector>

typedef vector<Item> Items;

class Player
{
public:
	Player();
	void init(int level, int health, int attack, float defense, int experience, int nxtLvlXP, int money);

	// Принимаем удар
	int takeDamage(int attack);

	// Дать герою объект
	//void giveItem(Item item);
	bool buyItem(Item item);

	// Возвращает размер урона от атаки моба
	int attack()const;

	// Upgrade item
	bool upgradeItem(Item & item);

	// Setters
	void setPosition(COORD coord);
	void addExperience(int experience);
	void addMoney(int money);

	// Getters
	COORD getPosition()const;
	int getLevel()const;
	int getHealth()const;
	int getMaxHealt()const;
	int getAttack()const;
	float getDefense()const;
	int getExperience()const;
	int getXPProgress()const;
	int getNextLevelXP()const;
	int getMoney()const;
	bool isItem(int id)const;
	bool isAlife()const;

private:
	// Characters
	int m_level;
	int m_health;
	int m_maxHealth;
	int m_attack;
	float m_defense;
	int m_experience;
	int m_nextLevelXP;
	int m_money;
	 
	// Position
	COORD m_coord;

public:
	Items m_items;
};