#pragma once
#include <string>
//#include "Player.h
#include "Level.h"

using namespace std;

class GameSystem
{
public:
	GameSystem(string levelFileName);

	void PlayGame();
	void playerMove();

private:
	Level _level;
	Player _player;
};