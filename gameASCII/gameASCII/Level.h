#pragma once

#include <string>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "NPC.h"
#include "global.h"
using namespace std;

#define LOG_MAX 4

class Level{
public:
	Level(){};

	void load(string fileName, Player &player);

	// Отрисовка инфы и карты
	void rewriteMap(Player player);
	void rewritePlayerInfo(Player player);

	// Вывод лога	
	void writeLog(string str);

	void movePlayer(short move, Player &player);
	void updateEnemies(Player &player);
	//Getters
	char getTile(COORD coord);
	int getNumsOfEnemies()const;
	//Setters
	void setTile(COORD coord, char tile);

private:
	void processPlayerMove(Player &player, COORD targetCoord);
	void processEnemyMove(Player &player, int enemyIndex, COORD targetCoord);
	void battleMonster(Player &player, COORD targetCoord);
	void processNPCDialog(Player &player, COORD targetCoord);
	void initDialog(Player & player, NPC & npc);
	void initSellerDialog(Player & player, NPC & npc);
	void initSmithDialog(Player & player, NPC & npc);
	bool buyItem(Player & player, NPC & npc, short id);
	void openTheDoor(COORD coord);
private:
	vector<string> m_levelData;
	vector<Enemy> m_enemies;
	vector<NPC> m_NPC;

	deque<string> m_log;
};