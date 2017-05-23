#include "Enemy.h"
#include <random>
#include <ctime>


Enemy::Enemy(string name, char tile, int level, int attack, float defense, int health, int money, COORD coord)
{
	m_name = name;
	m_tile = tile;
	m_level = level;
	m_attack = attack;
	m_defense = defense;
	m_health = health;
	m_money = money;
	m_coord = coord;
}

//Sets the position of the enemy
void Enemy::setPosition(COORD coord)
{
	m_coord = coord;
}

//Gets the position of the enemy using reference variable
COORD Enemy::getPosition() const
{
	return m_coord;
}

int Enemy::attack()const{
	static default_random_engine randomEngine(unsigned(time(NULL)));
	uniform_int_distribution<int> attackRoll(0, m_attack);

	return attackRoll(randomEngine);
}

int Enemy::getReward()const{
	static default_random_engine randomEngine(unsigned(time(NULL)));
	uniform_int_distribution<int> rewardRoll(0, m_money);

	return rewardRoll(randomEngine);
}

int Enemy::takeDamage(int attack)
{
	attack *= float(1-m_defense);

	//check if the atack does damage
	if (attack > 0){
		m_health -= attack;

		if (m_health <= 0) // если ранение не совместимо с жизнью
			return m_level * 5; // возвращаем опыт соразмерно уровню моба
	}

	return -1; // или возвращаем -1, если ранение не критично
}

char Enemy::getMove(COORD playerCoord)
{
	static default_random_engine randomEngine(unsigned(time(NULL)));
	uniform_int_distribution<int> moveRoll(0, 7);
	uniform_int_distribution<int> distanseRoll(1, 4);
	
	int dx = m_coord.X - playerCoord.X;
	int dy = m_coord.Y - playerCoord.Y;
	int adx = abs(dx);
	int ady = abs(dy);

	int distance = adx + ady;


	//Здесь добавить процедуру построения кратчайшего маршрута до игрока и одного хода по этому маршруту
	if (distance <= 5)
	{
		// Первым делом забываем про маршрут
		while (!route.empty())
			route.pop();

	/*	short localMap[11][11];
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if ((m_x + (j - 5) < 0) || (m_y + (i - 5) < 0))
				{
					localMap[i][j] = -1;
					continue;
				}
		
				if (getTile(j, i))
					localMap[i][j] = 0;
			}
		}
	}else{
	*/
		if (adx > ady) //Moving along X axis
			if (dx > 0)
				return MOVE_LEFT;
			else
				return MOVE_RIGHT;
		else //Move along Y axis
			if (dy > 0)
				return MOVE_UP;
			else
				return MOVE_DOWN;
	}

	if (route.empty())
	{
		int direct = moveRoll(randomEngine); // Movings direct
		int dist = distanseRoll(randomEngine); // Movings distance

		char step;
		
		switch (direct)
		{
		case 0:
			step = MOVE_LEFT;
			break;
		case 1:
			step = MOVE_UP;
			break;
		case 2:
			step = MOVE_RIGHT;
			break;
		case 3:
			step = MOVE_DOWN;
			break;
		default:
			step = STAY;
		}

		for (int i = 0; i < dist; i++)
			route.push(step);
	}

	char step = route.top();
	route.pop();

	return step;
}

string Enemy::getName()const{ 
	return m_name; 
}
char Enemy::getTile()const{ 
	return m_tile; 
}