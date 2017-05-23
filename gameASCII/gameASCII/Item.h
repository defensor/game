#pragma once
#include <iostream>
using namespace std;

#define BASE_LVL_UPDATE_DIFERENCE 5

class Item
{
public:
	Item();
	Item(string name, int price, int updatePrice, float defense, int damage, short level, float defenceUpdateDifference, float damageUpdateDifference);

	// Getters
	string getName()const;
	int getPrice()const;
	int getUpdatePrice()const;
	float getDefense()const;
	int getDamage()const;
	short getLevel()const;
	float getDefenceUpdateDifference()const;
	int getDamageUpdateDifference()const;

	//Level update
	void levelUp();
private:
	string m_name;
	int m_price;
	int m_baseUpdatePrice;
	float m_defenceUpdateDifference;
	float m_damageUpdateDifference;

	float m_defense;
	int m_damage;
	short m_level;
};