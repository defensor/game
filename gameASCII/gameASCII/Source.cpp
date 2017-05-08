#include <iostream>
#include "GameSystem.h"
#include "MenuItem.h"
#include <conio.h>

using namespace std;

#define MENU_ELEMENTS_NUM 2
// ������ ����
const COORD WINDOW_SIZE = { 80, 80 };

void printMenu(MenuItem * mi, size_t size);
void newGame();
void quit();

int main(){

	// �������� ������� ���� � ����������� �� ����� ���������
	// ���������� ���� �������
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { WINDOW_SIZE.X, WINDOW_SIZE.Y };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(hConsoleHandle, true, &src);
	SetConsoleScreenBufferSize(hConsoleHandle, crd);

	// ������ ���� ������ � ������� �� ������-������� (��� �� ���������)))
	SetColor(LightGreen, Black);

	MenuItem menuItems[MENU_ELEMENTS_NUM] = {
		MenuItem(0, "New Game", { 30, 20 }, false, true, true, true, LightGreen, LightGray, LightBlue, NULL, NULL, NULL, NULL, NULL, newGame),
		MenuItem(1, "Quit", { 30, 25 }, false, true, false, true, LightGreen, LightGray, LightBlue, NULL, NULL, NULL, NULL, NULL, quit)
	};
	menuItems[0].setNext(&menuItems[1]);
	menuItems[1].setNext(&menuItems[0]);
	//
	menuItems[0].setPrev(&menuItems[1]);
	menuItems[1].setPrev(&menuItems[0]);

	// ���� ����
	MenuItem * pMI = &menuItems[0];
	while (true){
		// ��������� ����
		printMenu(menuItems, MENU_ELEMENTS_NUM);

		// ��������� �������
		int code = _getch();
		if (code == 0 || code == 224)	// ���� ������ ������ ����������
			code = _getch();			// �� ������ ������������ ������

		// ������ ������� �������
		switch (code){
		case BTN_ENTER:		// Enter
				pMI->action();			// ���������� ��������� �������
			break;

		case BTN_UP:	// �����
				pMI = pMI->goPrev();	// ��������� � ����������� ��������
			break;

		case BTN_DOWN:	// ����
				pMI = pMI->goNext();	// ��������� � ���������� ��������
			break;
		}

	}
	return 0;
}

void newGame(){
	GameSystem gameSystem("levels\\level1.txt");
	gameSystem.PlayGame();
	system("cls");
	
}

void quit(){
	exit(0);
}

void printMenu(MenuItem * mi, size_t size){
	system("cls");

	for (size_t i = 0; i < size; i++)
		mi[i].print();
}