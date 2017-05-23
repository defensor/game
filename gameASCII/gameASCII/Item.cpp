#include "Item.h"

Item::Item(string name, int price, int updatePrice, float defense = 0, int damage = 0, short level = 0, 
		float defenceUpdateDifference = 0, float damageUpdateDifference = 0) :
m_name(name), m_price(price), m_baseUpdatePrice(updatePrice), m_defense(defense), m_damage(damage), 
m_level(level), m_defenceUpdateDifference(defenceUpdateDifference), m_damageUpdateDifference(damageUpdateDifference)
{
}

Item::Item() :
m_name(""), m_price(0), m_baseUpdatePrice(0), m_defense(0), m_damage(0),
m_level(0), m_defenceUpdateDifference(0), m_damageUpdateDifference(0)
{

}

string Item::getName()const{ 
	return m_name; 
}

int Item::getPrice()const{ 
	return m_price; 
}

int Item::getUpdatePrice()const{ 
	return m_baseUpdatePrice + BASE_LVL_UPDATE_DIFERENCE * m_level;; 
}

float Item::getDefense()const{ 
	return m_defense + m_defenceUpdateDifference * m_level;
}

int Item::getDamage()const{ 
	return m_damage + m_damageUpdateDifference * m_level; 
}

short Item::getLevel()const{ 
	return m_level; 
}

float Item::getDefenceUpdateDifference()const{ 
	return m_defenceUpdateDifference; 
}

int Item::getDamageUpdateDifference()const{ 
	return m_damageUpdateDifference; 
}

void Item::levelUp(){ 
	m_level++; 
}