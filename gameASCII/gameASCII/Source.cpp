#include <iostream>
#include "GameSystem.h"
#include "MenuItem.h"
#include <conio.h>

using namespace std;

#define MENU_ELEMENTS_NUM 2
// Размер окна
const COORD WINDOW_SIZE = { 80, 80 };

void printMenu(MenuItem * mi, size_t size);
void newGame();
void quit();

int main(){

	// Изменяем размеры окна и избавляемся от полос прокрутки
	// Дескриптор окна консоли
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { WINDOW_SIZE.X, WINDOW_SIZE.Y };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(hConsoleHandle, true, &src);
	SetConsoleScreenBufferSize(hConsoleHandle, crd);

	// Меняем цвет текста в консоли на светло-зеленый (шоб по хацкерски)))
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

	// Цикл меню
	MenuItem * pMI = &menuItems[0];
	while (true){
		// Отрисовка меню
		printMenu(menuItems, MENU_ELEMENTS_NUM);

		// Считываем команду
		int code = _getch();
		if (code == 0 || code == 224)	// Если первый символ конмандный
			code = _getch();			// то читаем опциональный символ

		// Анализ нажатой клавиши
		switch (code){
		case BTN_ENTER:		// Enter
				pMI->action();			// вызывается связанная функция
			break;

		case BTN_UP:	// Вверх
				pMI = pMI->goPrev();	// переходим к предыдущему элементу
			break;

		case BTN_DOWN:	// Вниз
				pMI = pMI->goNext();	// переходим к следующему элементу
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