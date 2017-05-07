#include "GameSystem.h"
#include <conio.h>

//Constructor sets up the game
GameSystem::GameSystem(string levelFileName)
{
	_player.init(1, 100, 10, 0, 0, 0);
	_level.load(levelFileName, _player);

	system("PAUSE");
}

void GameSystem::PlayGame()
{
	_level.rewriteMap(_player);

	while (_level.getNumsOfEnemies() > 0)
	{
		_level.updateEnemies(_player);
		playerMove();	
	}
}

void GameSystem::playerMove()
{
	short move = STAY;

	switch (_getch())
	{
	case 'w': //up
	case 'W':
	case 'k':
		move = MOVE_UP;
		break;
	case 's': //down
	case 'S':
	case 'j':
		move = MOVE_DOWN;
		break;
	case 'a': //left
	case 'A':
	case 'h':
		move = MOVE_LEFT;
		break;
	case 'd': //right
	case 'D':
	case 'l':
		move = MOVE_RIGHT;
		break;
	}

	_level.movePlayer(move, _player);
}