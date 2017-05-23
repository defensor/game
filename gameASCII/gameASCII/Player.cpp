#include "Player.h"
#include <random>
#include <ctime>

using namespace std;

//Constructor just initializes position to zero
Player::Player(){
	m_coord = { 0, 0 };
	m_money = 0;
	m_level = 0;
	m_health = m_maxHealth = 100;
	m_nextLevelXP = 50;
	m_attack = 10;
	m_defense = 0;
	m_experience = 0;
	m_nextLevelXP = 0;
}

//Initializes with player with properties
void Player::init(int level, int health, int attack, float defense = 0, int experience = 0, int nxtLvlXP = 50, int money = 0){
	m_level = level;
	m_health = m_maxHealth = health;
	m_attack = attack;
	m_defense = defense;
	m_experience = experience;
	m_money = money;
	m_nextLevelXP = nxtLvlXP;
}

int Player::attack()const{
	static default_random_engine randomEngine(unsigned(time(NULL)));
	uniform_int_distribution<int> attackRoll(0, m_attack);

	return attackRoll(randomEngine);
}

//Sets the position of the player
void Player::setPosition(COORD coord){
	m_coord = coord;
}

//Gets the position of the player using reference variable
COORD Player::getPosition() const{
	return m_coord;
}

void Player::addExperience(int experience){
	m_experience += experience;

	//Level Up!
	while (m_experience >= m_nextLevelXP){
		// lvlup!
		m_experience -= m_nextLevelXP;
		m_level++;
		// Плюшки
		m_attack += m_level * 5;
		m_maxHealth += 10;
		m_health = m_maxHealth;
		m_nextLevelXP += 10;
	}
}

int Player::takeDamage(int attack){
	attack *= (1 - m_defense);

	//check if the atack does damage
	if (attack > 0){
		m_health -= attack;
		//check if he died
		if (m_health <= 0){
			m_health = 0;
			return 1;
		}
	}

	return -1;
}

//void Player::giveItem(Item  item){
//	_items.push_back(item);
//}
bool Player::buyItem(Item item){
	int price = item.getPrice();
	if (m_money >= price)
	{
		m_money -= price;
		m_items.push_back(item);
		
		return true;
	}

	return false;
}

void Player::addMoney(int money){
	m_money += money;
}


bool Player::isItem(int id) const{
	return (id >= 0 && id < m_items.size());
}


bool Player::upgradeItem(Item & item){
	int price = item.getUpdatePrice();
	if (m_money >= price){ // Если достаточно денег для апгрейда
		m_money -= price;
		item.levelUp();

		return true;
	}
	
	return false;
}

float Player::getDefense()const{
	float defense = m_defense;
	for (vector<Item>::const_iterator ci = m_items.begin(); ci < m_items.end(); ci++)
		defense += ci->getDefense();


	return defense;
}

int Player::getAttack()const{
	int attack = m_attack;
	for (vector<Item>::const_iterator ci = m_items.begin(); ci < m_items.end(); ci++)
		attack += ci->getDamage();

	return attack;
}

bool Player::isAlife()const{
	return m_health > 0;
}

int Player::getLevel()const{ 
	return m_level; 
}

int Player::getHealth()const{ 
	return m_health; 
}

int Player::getMaxHealt()const{
	return m_maxHealth; 
}

int Player::getExperience()const{ 
	return m_experience;
}

int Player::getXPProgress()const{ 
	return (int)((m_experience / m_nextLevelXP) * 100); 
}

int Player::getNextLevelXP()const{ 
	return m_nextLevelXP; 
}

int Player::getMoney()const{ 
	return m_money; 
}