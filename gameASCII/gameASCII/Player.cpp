#include "Player.h"
#include <random>
#include <ctime>

using namespace std;

//Constructor just initializes position to zero
Player::Player(){
	_x = 0;
	_y = 0;
	_money = 0;
	_level = 0;
	_health = _maxHealth = 100;
	_nextLevelXP = 50;
	_attack = 10;
	_defense = 0;
	_experience = 0;
	_nextLevelXP = 0;
}

//Initializes with player with properties
void Player::init(int level, int health, int attack, float defense = 0, int experience = 0, int nxtLvlXP = 50, int money = 0){
	_level = level;
	_health = _maxHealth = health;
	_attack = attack;
	_defense = defense;
	_experience = experience;
	_money = money;
	_nextLevelXP = nxtLvlXP;
}

int Player::attack()const{
	static default_random_engine randomEngine(unsigned(time(NULL)));
	uniform_int_distribution<int> attackRoll(0, _attack);

	return attackRoll(randomEngine);
}

//Sets the position of the player
void Player::setPosition(int x, int y){
	_x = x;
	_y = y;
}

//Gets the position of the player using reference variable
void Player::getPosition(int &x, int &y) const{
	x = _x;
	y = _y;
}

void Player::addExperience(int experience){
	_experience += experience;

	//Level Up!
	while (_experience >= _nextLevelXP){
		// lvlup!
		_experience -= _nextLevelXP;
		_level++;
		// Плюшки
		_attack += _level * 5;
		_maxHealth += 10;
		_health = _maxHealth;
		_nextLevelXP += 10;
	}
}

int Player::takeDamage(int attack){
	attack *= (1 - _defense);

	//check if the atack does damage
	if (attack > 0){
		_health -= attack;
		//check if he died
		if (_health <= 0){
			_health = 0;
			return 1;
		}
	}

	return -1;
}

void Player::giveItem(Item  item){
	_items.push_back(item);
}

void Player::addMoney(int money){
	_money += money;
}


bool Player::isItem(int id) const{
	return (id >= 0 && id < _items.size());
}


bool Player::upgradeItem(Item & item){
	int price = item.getUpdatePrice();
	if (_money >= price){ // Если достаточно денег для апгрейда
		_money -= price;
		item.levelUp();

		return true;
	}
	
	return false;
}

float Player::getDefense()const{
	float defense = _defense;
	for (vector<Item>::const_iterator ci = _items.begin(); ci < _items.end(); ci++)
		defense += ci->getDefense();


	return defense;
}

int Player::getAttack()const{
	int attack = _attack;
	for (vector<Item>::const_iterator ci = _items.begin(); ci < _items.end(); ci++)
		attack += ci->getDamage();

	return attack;
}