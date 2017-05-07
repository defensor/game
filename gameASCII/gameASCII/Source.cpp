#include <iostream>
#include "GameSystem.h"

using namespace std;

int main()
{
	GameSystem gameSystem("levels\\level1.txt");

	gameSystem.PlayGame();

	system("cls");

	printf("You WIN!!!\n");

	return 0;
}