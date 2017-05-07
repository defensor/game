#include "Level.h"
#include <fstream>
#include <iostream>
//#include <cstdio>
#include <conio.h>
#include <ctime>
#include <Windows.h>

HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);	// Дескриптор окна консоли
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
		_levelData.push_back(line);
	}

	file.close();

	//Process the level
	char tile;

	for (size_t i = 0; i < _levelData.size(); i++)
		for (size_t j = 0; j < _levelData[i].size(); j++)
		{
			tile = _levelData[i][j];
			
			switch (tile)
			{
			case PLAYER_TILE: //Player
				player.setPosition(j, i);
				break;
			case SELLER_TILE: //Seller
				_NPC.push_back(NPC(tile));
				_NPC.back().setPosition(j, i);
				_NPC.back()._items.push_back(Item("Armor", 70, 5, 0.2, 0, 1, 0.03, 0));
				_NPC.back()._items.push_back(Item("Sword", 50, 5, 0, 0.2, 1, 0, 0.03));
				break;
			case SMITH_TILE: //Koval
				_NPC.push_back(NPC(tile));
				_NPC.back().setPosition(j, i);
				break;
			case SNAKE_TILE: //Snake
				_enemies.push_back(Enemy("Snake", tile, 1, 3, 0, 10, 50, 10));
				_enemies.back().setPosition(j, i);
				break;
			case GOBLIN_TILE: //Goblin
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 0.05, 35, 150, 15));
				_enemies.back().setPosition(j, i);
				break;
			case BANDIT_TILE: //Bandit
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 0.1, 100, 250, 30));
				_enemies.back().setPosition(j, i);
				break;
			case OGRE_TILE: //Ogre
				_enemies.push_back(Enemy("Ogre", tile, 4, 40, 0.4, 200, 500, 50));
				_enemies.back().setPosition(j, i);
				break;
			case GOLEM_TILE: //Golem
				_enemies.push_back(Enemy("Golem", tile, 20, 150, 0.5, 300, 1000, 100));
				_enemies.back().setPosition(j, i);
				break;
			case DRAGON_TILE: //Dragon
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 0.0, 1500, 99999, 1000));
				_enemies.back().setPosition(j, i);
				break;
			case UNDEAD_TILE: //Undead
				_enemies.push_back(Enemy("Undead", tile, 1, 100000, 1, 1, 0, 0));
				_enemies.back().setPosition(j, i);
				break;
			}
		}
}

void Level::rewriteMap(Player player){
	system("cls");

	rewritePlayerInfo(player);

	for (vector<string>::const_iterator ci = _levelData.begin(); ci < _levelData.end(); ci++)
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
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);


	switch (move)
	{
	case MOVE_UP:
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case MOVE_DOWN:
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case MOVE_LEFT:
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case MOVE_RIGHT:
		processPlayerMove(player, playerX + 1, playerY);
		break;
	case STAY:
		break;
	}
}

char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile)
{
	// Отрисовка символа по позиции
	_levelData[y][x] = tile;

	SetConsoleCursorPosition(hConsoleHandle, { x + MAP_POS.X, y + MAP_POS.Y});
	std::cout << tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY)
{
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
	case SPACE_TILE:
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, SPACE_TILE);
		setTile(targetX, targetY, PLAYER_TILE);
		break;
	case STONE_TILE:
		break;
	case SELLER_TILE:
		//cout << "Pressed 'E' for dialog." << endl;
		processNPCDialog(player, targetX, targetY);
		break;
	case SMITH_TILE:
		processNPCDialog(player, targetX, targetY);
	case VDOOR_TILE:
	case HDOOR_TILE:
		openTheDoor(targetX, targetY);
		break;
	default:
		battleMonster(player, targetX, targetY);
		break;
	}
}

void Level::battleMonster(Player &player, int targetX, int targetY)
{
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackRoll;
	int attackResult;
	int money;
	string enemyName;

	player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].getName();

		if ((enemyX == targetX) && (enemyY == targetY))
		{
			//Battle!
			attackRoll = player.attack();

			
			writeLog("Player -> " + enemyName + " : " + std::to_string(attackRoll));
			attackResult = _enemies[i].takeDamage(attackRoll);
			
			srand(unsigned(time(NULL)));
			
			if (attackResult != 0)
			{
				money = _enemies[i].getMoney() * (rand() % 8 + 2) / 10;
				// Отрисовка карты
				setTile(targetX, targetY, SPACE_TILE);
				// Отображение надписи
				writeLog(enemyName + " died!");
				//Remove the enemy
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;
				player.addExperience(attackResult);
				player.addMoney(money);
				
				rewritePlayerInfo(player);
				return;
			}

			//Monster turns!
			attackRoll = _enemies[i].attack();
			// Отображение надписи
			writeLog(enemyName + " -> player : " + std::to_string(attackRoll));

			attackResult = player.takeDamage(attackRoll);
			if (attackResult != 0)
			{
				setTile(playerX, playerY, 'X');
				rewritePlayerInfo(player);
				// Отображение надписи
				writeLog("You died!");
				system("PAUSE");

				exit(0);
			}

			rewritePlayerInfo(player);
			return;
		}
	}
}

void Level::updateEnemies(Player &player)
{
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	player.getPosition(playerX, playerY);
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i].getPosition(enemyX, enemyY);
		aiMove = _enemies[i].getMove(playerX, playerY);

		switch (aiMove)
		{
		case MOVE_UP: //up
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case MOVE_DOWN: //down
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case MOVE_LEFT: //left
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case MOVE_RIGHT: //right
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
	}
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY)
{
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile)
	{
	case SPACE_TILE:
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, SPACE_TILE);
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case PLAYER_TILE:
		battleMonster(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Level::processNPCDialog(Player &player, int targetX, int targetY)
{
	int npcX;
	int npcY;
	int playerX;
	int playerY;
	string npcName;

	player.getPosition(playerX, playerY);

	for (size_t i = 0; i < _NPC.size(); i++)
	{
		_NPC[i].getPosition(npcX, npcY);

		if ((npcX == targetX) && (npcY == targetY))
		{
			initDialog(player, _NPC[i]);
			break;
		}
	}
}

void Level::openTheDoor(int x, int y)
{
	if (getTile(x, y) == HDOOR_TILE || getTile(x, y) == VDOOR_TILE)
		setTile(x, y, SPACE_TILE);
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
	npc.showSmithDialog(player._items, player.getMoney());

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
		for (i = 0; i < player._items.size(); i++)
		{
			if (player._items[i].getLevel() == 10)
				continue;
			if (id == choice)
				break;
			id++;
		}

		if (i == player._items.size())
			continue;

		Item & item = player._items.at(i);

		if (player.upgradeItem(item))
			npc.showSmithDialog(player._items, player.getMoney());

		player.reloadItem();
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

		if (buyItem(player, npc, int(choice) - '0'))
			npc.showSellerDialog(player.getMoney());

		player.reloadItem();
	}

	rewriteMap(player);
}

bool Level::buyItem(Player & player, NPC & npc, short id)
{
	id--;
	if (npc.isItem(id))
	{
		int price = npc._items[id].getPrice();
		if (player.getMoney() >= price)
		{
			player.subMoney(price);
			player.giveItem(npc.gettingItem(id));
			player.reloadItem();
			return true;
		}
	}
	return false;
}

void Level::writeLog(string str){
	_log.push_front(str);

	if (_log.size() > LOG_MAX)
		_log.pop_back();

	for (int i = 0; i < LOG_MAX; i++){
		SetConsoleCursorPosition(hConsoleHandle, { TXT_OUT_POS.X, TXT_OUT_POS.Y + i });
		printf("                                                                    ");
	}

	for (int i = 0; i < _log.size(); i++){
		SetConsoleCursorPosition(hConsoleHandle, { TXT_OUT_POS.X, TXT_OUT_POS.Y + i });
		cout << _log[i];
	}
}