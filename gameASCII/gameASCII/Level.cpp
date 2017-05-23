#include "Level.h"
#include <fstream>
#include <iostream>
//#include <cstdio>
#include <conio.h>
#include <ctime>
#include <Windows.h>

// Дескриптор окна консоли
HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// Флаги отрисовки
bool bPlayerInfoRewrite = true;
bool bMapRewrite = true;
// Координаты
const COORD MAP_POS = { 0, 5 };
const COORD TXT_OUT_POS = { 0, 30 };

void Level::load(string fileName, Player &player)
{
	ifstream file;

	file.open(fileName);
	if (file.fail())
	{
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	string line;

	while (getline(file, line))
	{
		m_levelData.push_back(line);
	}

	file.close();

	//Process the level
	char tile;

	COORD p;

	for (p.Y = 0; p.Y < m_levelData.size(); p.Y++)
		for (p.X = 0; p.X < m_levelData[p.Y].size(); p.X++)
		{
			tile = m_levelData[p.Y][p.X];
			
			switch (tile)
			{
			case PLAYER_TILE: //Player
				player.setPosition(p);
				break;
			case SELLER_TILE: //Seller
				m_NPC.push_back(NPC("Seller", tile, p));
				m_NPC.back().m_items.push_back(Item("Armor", 70, 5, .2, 0, 1, .03, 0));
				m_NPC.back().m_items.push_back(Item("Sword", 50, 5, 0, .2, 1, 0, 3));
				break;
			case SMITH_TILE: //Koval
				m_NPC.push_back(NPC("Smith", tile, p));
				break;
			case SNAKE_TILE: //Snake
				m_enemies.push_back(Enemy("Snake", tile, 1, 3, 0, 10, 10, p));
				break;
			case GOBLIN_TILE: //Goblin
				m_enemies.push_back(Enemy("Goblin", tile, 2, 10, .05, 35, 15, p));
				break;
			case BANDIT_TILE: //Bandit
				m_enemies.push_back(Enemy("Bandit", tile, 3, 15, .1, 100, 30, p));
				break;
			case OGRE_TILE: //Ogre
				m_enemies.push_back(Enemy("Ogre", tile, 4, 40, .4, 200, 50, p));
				break;
			case GOLEM_TILE: //Golem
				m_enemies.push_back(Enemy("Golem", tile, 20, 150, .5, 300, 100, p));
				break;
			case DRAGON_TILE: //Dragon
				m_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 0, 1500, 1000, p));
				break;
			case UNDEAD_TILE: //Undead
				m_enemies.push_back(Enemy("Undead", tile, 1, 100000, 1, 1, 0, p));
				break;
			}
		}
}

void Level::rewriteMap(Player player){
	system("cls");

	rewritePlayerInfo(player);

	for (vector<string>::const_iterator ci = m_levelData.begin(); ci < m_levelData.end(); ci++)
		printf("%s\n", ci->c_str());
}

void Level::rewritePlayerInfo(Player player){
	SetConsoleCursorPosition(hConsoleHandle, { 0, 0 });
	printf("\t\t\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t\n");
	SetConsoleCursorPosition(hConsoleHandle, { 0, 0 });
	printf("%dlvl  %d/%d XP\n", player.getLevel(), player.getExperience(), player.getNextLevelXP());
	printf("%d/%dhp\n", player.getHealth(), player.getMaxHealt());
	printf("Attack: %d\n", player.getAttack());
	printf("Defense: %d%\n", (int)(player.getDefense() * 100));
	printf("%d$\n", player.getMoney());
}

void Level::movePlayer(short move, Player &player)
{
	COORD playerCoord;

	playerCoord = player.getPosition();


	switch (move)
	{
	case MOVE_UP:
		processPlayerMove(player, { playerCoord.X, playerCoord.Y - 1 });
		break;
	case MOVE_DOWN:
		processPlayerMove(player, { playerCoord.X, playerCoord.Y + 1 });
		break;
	case MOVE_LEFT:
		processPlayerMove(player, { playerCoord.X - 1, playerCoord.Y });
		break;
	case MOVE_RIGHT:
		processPlayerMove(player, { playerCoord.X + 1, playerCoord.Y });
		break;
	case STAY:
		break;
	}
}

char Level::getTile(COORD coord)
{
	return m_levelData[coord.Y][coord.X];
}

void Level::setTile(COORD coord, char tile)
{
	// Отрисовка символа по позиции
	m_levelData[coord.Y][coord.X] = tile;

	SetConsoleCursorPosition(hConsoleHandle, { coord.X + MAP_POS.X, coord.Y + MAP_POS.Y});
	std::cout << tile;
}

void Level::processPlayerMove(Player &player, COORD targetCoord)
{
	COORD playerCoord;

	playerCoord = player.getPosition();

	char moveTile = getTile(targetCoord);

	switch (moveTile)
	{
	case SPACE_TILE:
		player.setPosition(targetCoord);
		setTile(playerCoord, SPACE_TILE);
		setTile(targetCoord, PLAYER_TILE);
		break;
	case STONE_TILE:
		break;
	case SELLER_TILE:
		//cout << "Pressed 'E' for dialog." << endl;
		processNPCDialog(player, targetCoord);
		break;
	case SMITH_TILE:
		processNPCDialog(player, targetCoord);
	case VDOOR_TILE:
	case HDOOR_TILE:
		openTheDoor(targetCoord);
		break;
	default:
		battleMonster(player, targetCoord);
		break;
	}
}

void Level::battleMonster(Player &player, COORD targetCoord)
{
	COORD enemyCoord;
	COORD playerCoord;
	int attackRoll;
	int attackResult;
	int money;
	string enemyName;

	playerCoord = player.getPosition();

	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		enemyCoord = m_enemies[i].getPosition();
		enemyName = m_enemies[i].getName();

		if ((enemyCoord.X == targetCoord.X) && (enemyCoord.Y == targetCoord.Y))
		{
			//Battle!
			// Первым атакует герой
			attackRoll = player.attack();
			
			writeLog("Player -> " + enemyName + " : " + std::to_string(attackRoll));
			attackResult = m_enemies[i].takeDamage(attackRoll);
			
			srand(unsigned(time(NULL)));
			
			if (attackResult != -1)
			{
				money = m_enemies[i].getReward();
				// Отрисовка карты
				setTile(targetCoord, SPACE_TILE);
				// Отображение надписи
				writeLog(enemyName + " died!");
				//Remove the enemy
				m_enemies[i] = m_enemies.back();
				m_enemies.pop_back();
				i--;
				player.addExperience(attackResult);
				player.addMoney(money);
				
				rewritePlayerInfo(player);
				if (m_enemies.empty())
					writeLog("You WIN!!!");
				return;
			}

			//Monster turns!
			attackRoll = m_enemies[i].attack();
			// Отображение надписи
			writeLog(enemyName + " -> player : " + std::to_string(attackRoll));

			attackResult = player.takeDamage(attackRoll);
			if (attackResult != -1)
			{
				// Кто-то умер
				setTile(playerCoord, 'X');
				rewritePlayerInfo(player);
				writeLog("You died!");
				return;
			}

			rewritePlayerInfo(player);
			return;
		}
	}
}

void Level::updateEnemies(Player &player)
{
	char aiMove;
	COORD playerCoord;
	COORD enemyCoord;

	playerCoord = player.getPosition();
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		enemyCoord = m_enemies[i].getPosition();
		aiMove = m_enemies[i].getMove(playerCoord);

		switch (aiMove)
		{
		case MOVE_UP: //up
			processEnemyMove(player, i, {enemyCoord.X, enemyCoord.Y - 1	});
			break;
		case MOVE_DOWN: //down
			processEnemyMove(player, i, { enemyCoord.X, enemyCoord.Y + 1 });
			break;
		case MOVE_LEFT: //left
			processEnemyMove(player, i, { enemyCoord.X - 1, enemyCoord.Y });
			break;
		case MOVE_RIGHT: //right
			processEnemyMove(player, i, { enemyCoord.X + 1, enemyCoord.Y });
			break;
		}
	}
}

void Level::processEnemyMove(Player &player, int enemyIndex, COORD targetCoord)
{
	COORD playerCoord;
	COORD enemyCoord;

	enemyCoord = m_enemies[enemyIndex].getPosition();
	playerCoord = player.getPosition();

	char moveTile = getTile(targetCoord);

	switch (moveTile)
	{
	case SPACE_TILE:
		m_enemies[enemyIndex].setPosition(targetCoord);
		setTile(enemyCoord, SPACE_TILE);
		setTile(targetCoord, m_enemies[enemyIndex].getTile());
		break;
	case PLAYER_TILE:
		battleMonster(player, enemyCoord);
		break;
	default:
		break;
	}
}

void Level::processNPCDialog(Player &player, COORD targetCoord)
{
	COORD npcCoord;
	COORD playerCoord;
	string npcName;

	playerCoord = player.getPosition();

	for (size_t i = 0; i < m_NPC.size(); i++)
	{
		npcCoord = m_NPC[i].getPosition();
		
		if ((npcCoord.X == targetCoord.X) && (npcCoord.Y == targetCoord.Y))
		{
			initDialog(player, m_NPC[i]);
			break;
		}
	}
}

void Level::openTheDoor(COORD coord)
{
	if (getTile(coord) == HDOOR_TILE || getTile(coord) == VDOOR_TILE)
		setTile(coord, SPACE_TILE);
}

void Level::initDialog(Player & player, NPC & npc)
{
	switch (npc.getTile())
	{
	case SELLER_TILE:
		initSellerDialog(player, npc);
		break;
	case SMITH_TILE:
		initSmithDialog(player, npc);
		break;
	}
}

void Level::initSmithDialog(Player & player, NPC & npc)
{
	npc.showSmithDialog(player.m_items, player.getMoney());

	char choice = ' ';
	while (true)
	{
		choice = _getch();

		if (choice == '0')
			break;

		choice -= '1';

		if (!player.isItem(choice))
			continue;

		int id = 0;
		size_t i;
		for (i = 0; i < player.m_items.size(); i++)
		{
			if (player.m_items[i].getLevel() == 10)
				continue;
			if (id == choice)
				break;
			id++;
		}

		if (i == player.m_items.size())
			continue;

		Item & item = player.m_items.at(i);

		if (player.upgradeItem(item))
			npc.showSmithDialog(player.m_items, player.getMoney());
	}

	rewriteMap(player);
}

void Level::initSellerDialog(Player & player, NPC & npc)
{
	npc.showSellerDialog(player.getMoney());

	char choice = ' ';
	while (true)
	{
		choice = _getch();

		if (choice == '0')
			break;

		if (buyItem(player, npc, int(choice) - '0')){
			npc.showSellerDialog(player.getMoney());
		}
	}

	rewriteMap(player);
}

bool Level::buyItem(Player & player, NPC & npc, short id)
{
	id--;
	if (npc.isItem(id))
	{
		if (player.buyItem(npc.m_items[id]))
			npc.removeItem(id);
		else
			return false;

			return true;
	}

	return false;
}

void Level::writeLog(string str){
	m_log.push_front(str);

	if (m_log.size() > LOG_MAX)
		m_log.pop_back();

	for (int i = 0; i < LOG_MAX; i++){
		SetConsoleCursorPosition(hConsoleHandle, { TXT_OUT_POS.X, TXT_OUT_POS.Y + i });
		printf("                                                                    ");
	}

	for (size_t i = 0; i < m_log.size(); i++){
		SetConsoleCursorPosition(hConsoleHandle, { TXT_OUT_POS.X, TXT_OUT_POS.Y + i });
		cout << m_log[i];
	}
}

int Level::getNumsOfEnemies()const{ 
	return m_enemies.size(); 
}