#include "Item.h"

Item::Item(string name, int price, int updatePrice, float defense = 0, float damage = 0, short level = 0, 
		float defenceUpdateDifference = 0, float damageUpdateDifference = 0) :
_name(name), _price(price), _baseUpdatePrice(updatePrice), _defense(defense), _damage(damage), 
_level(level), _defenceUpdateDifference(defenceUpdateDifference), _damageUpdateDifference(damageUpdateDifference)
{
}

Item::Item() :
_name(""), _price(0), _baseUpdatePrice(0), _defense(0), _damage(0),
_level(0), _defenceUpdateDifference(0), _damageUpdateDifference(0)
{

}