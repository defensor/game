#include "Player.h"
#include <random>
#include <ctime>

using namespace std;

//Constructor just initializes position to zero
Player::Player()
{
	_x = 0;
	_y = 0;
	_money = 0;
}

//Initializes with player with properties
void Player::init(int level, int health, int attack, float defense, int experience, int money)
{
	_level = level;
	_maxHealth = health;
	_health = health;
	_baseAttack = attack;
	_attack = attack;
	_defense = defense;
	_experience = experience;
	_money = money;
}

//Sets the position of the player
void Player::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

//Gets the position of the player using reference variable
void Player::getPosition(int &x, int &y) const
{
	x = _x;
	y = _y;
}

int Player::attack()
{
	static default_random_engine randomEngine(unsigned(time(NULL)));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

void Player::addExperience(int experience)
{
	_experience += experience;

	//Level Up!
	while (_experience >= _nextLevelXP)
	{
		_experience -= _nextLevelXP;
		_baseAttack += _level * 5;
		_maxHealth += 10;
		_health = _maxHealth;
		_nextLevelXP += 10;
		_level++;
	}
}

int Player::takeDamage(int attack)
{
	attack *= (1 - _defense);

	//check if the atack does damage
	if (attack > 0)
	{
		_health -= attack;
		//check if he died
		if (_health <= 0)
		{
			_health = 0;
			return 1;
		}
	}

	reloadItem();
	return 0;
}

void Player::giveItem(Item  item)
{
	_items.push_back(item);
}

void Player::reloadItem()
{
	_defense = 0;
	_attack = _baseAttack;
	for (vector<Item>::const_iterator ci = _items.begin(); ci < _items.end(); ci++)
	{
		_defense += ci->getDefense();
		_attack += int(ci->getDamage() * _baseAttack);
	}
}

void Player::addMoney(int money)
{
	_money += money;
}

void Player::subMoney(int money)
{
	_money -= money;
}

bool Player::isItem (int id) const
{
	return (id >= 0 && id < this->_items.size());
}

bool Player::upgradeItem(Item & item)
{
	int price = item.getUpdatePrice();
	if (this->getMoney() >= price)
	{
		this->subMoney(price);
		item.levelUp();
		this->reloadItem();
		return true;
	}
	
	return false;
}