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
	char getTile(int x, int y);
	int getNumsOfEnemies() { return _enemies.size(); }
	//Setters
	void setTile(int x, int y, char tile);

private:
	void processPlayerMove(Player &player, int targetX, int targetY);
	void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
	void battleMonster(Player &player, int targetX, int targetY);
	void processNPCDialog(Player &player, int targetX, int targetY);
	void initDialog(Player & player, NPC & npc);
	void initSellerDialog(Player & player, NPC & npc);
	void initSmithDialog(Player & player, NPC & npc);
	bool buyItem(Player & player, NPC & npc, short id);
	void openTheDoor(int x, int y);
private:
	vector<string> _levelData;
	vector<Enemy> _enemies;
	vector<NPC> _NPC;

	deque<string> _log;
};