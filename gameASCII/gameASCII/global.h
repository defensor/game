#pragma once
#include <Windows.h>

enum {
	SPACE_TILE = '.', PLAYER_TILE = '@', STONE_TILE = '#', VDOOR_TILE = '|', HDOOR_TILE = '-', GOBLIN_TILE = 'g', SNAKE_TILE = 's', BANDIT_TILE = 'B', OGRE_TILE = 'O', GOLEM_TILE = 'G', DRAGON_TILE = 'D', SMITH_TILE = '&', SELLER_TILE = '$', UNDEAD_TILE = '0'
};

// Перемещения персонажа
enum { STAY, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

