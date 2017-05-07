#pragma once
#include <iostream>
using namespace std;

#define BASE_LVL_UPDATE_DIFERENCE 5

class Item
{
public:
	Item();
	Item(string name, int price, int updatePrice, float defense, float damage, short level, float defenceUpdateDifference, float damageUpdateDifference);

	// Getters
	string getName()const{ return _name; }
	int getPrice()const{ return _price; }
	int getUpdatePrice()const{ return _baseUpdatePrice + BASE_LVL_UPDATE_DIFERENCE * this->_level;; }
	float getDefense()const{ return _defense + _defenceUpdateDifference * _level; }
	float getDamage()const{ return _damage + _damageUpdateDifference * _level; }
	short getLevel()const{ return _level; }
	float getDefenceUpdateDifference()const{ return _defenceUpdateDifference; }
	float getDamageUpdateDifference()const{ return _damageUpdateDifference; }

	//Level update
	void levelUp(){ this->_level++; };
private:
	string _name;
	int _price;
	int _baseUpdatePrice;
	float _defenceUpdateDifference;
	float _damageUpdateDifference;

	float _defense;
	float _damage;
	short _level;
};