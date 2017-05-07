#pragma once
#include <iostream>
#include <Windows.h>

using std::string;

// Константы цветов
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class MenuBlock;

// Коды клавиш
#define BTN_ESC 27
#define BTN_ENTER 13
#define BTN_LEFT 75
#define BTN_RIGHT 77
#define BTN_UP 72
#define BTN_DOWN 80

void SetColor(ConsoleColor text, ConsoleColor background);

// Класс элементов меню
class MenuItem
{
public:
	MenuItem(){}
	MenuItem(int id, string text, COORD coord, bool dropDown, bool visible, bool selected, bool active,
		ConsoleColor activeTxtClr, ConsoleColor inactiveTxtClr, ConsoleColor bkClrOfSelectedItem, 
		MenuItem * pNext, MenuItem * pPrev, MenuItem * pParent, MenuItem * pChild, MenuBlock * block, void(*pFunc)());

	//MenuItem(MenuItem & rhs);
	~MenuItem(){};

	// Getters
	int getId()const;
	
	string getStr()const;
	string getText()const;
	
	ConsoleColor getTxtClr()const;
	ConsoleColor getBkClr()const;
	ConsoleColor getActiveTxtClr()const;
	ConsoleColor getInactiveTxtClr()const;
	ConsoleColor getBkClrOfSlctdItem()const;
	
	COORD getPos()const;
	
	MenuItem * getParent()const;
	MenuItem * getChild()const;
	MenuItem * getNext()const;
	MenuItem * getPrev()const;

	MenuBlock * getBlock()const;

	bool isActive()const;
	bool isDropDown()const;
	bool isVisible()const;
	bool isSelected()const;

	void(*getFunc()const) ();

	// Setters
	void setId(int id);

	void setTxt(string txt);

	void setPos(COORD pos);

	void setParent(MenuItem * pParent);
	void setChild(MenuItem * pChild);
	void setNext(MenuItem * pNext);
	void setPrev(MenuItem * pPrev);

	void setBlock(MenuBlock * block);

	// Контроль флагов
	void activate();
	void deactivate();
	void show();
	void hide();
	void select();
	void deselect();

	// Функционал
	void print()const;
	void action();

	MenuItem * goNext();
	MenuItem * goPrev();
	MenuItem * drop();
	MenuItem * compress();

private:
	// Основные параметры элемента меню
	int m_id;
	string m_szText;
	COORD m_pos;
	bool m_bDropDown;
	bool m_bVisible;
	bool m_bSelected;
	bool m_bActive;

	// Цветовые параметры
	ConsoleColor m_activeTxtClr;
	ConsoleColor m_inactiveTxtClr;
	ConsoleColor m_bkClrOfSelectedItem;

	// Связи с другими пунктами меню
	MenuItem * m_pNext;
	MenuItem * m_pPrev;
	MenuItem * m_pParent;
	MenuItem * m_pChild;

	MenuBlock * m_menuBlock;

	void (*m_pFunc)();	// Указатель на функцию выполняемую данным пунктом меню
};

typedef MenuItem * PMenuItem;
int ChoiceMenu(MenuItem templ, string * names, size_t num, COORD start, COORD step, bool orientVert, bool canBack);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuBlock{
public:
	MenuBlock(size_t size, PMenuItem * block);
	MenuBlock(size_t size);
	~MenuBlock();

	bool getVisible()const;
	void setVisible(bool visible);

	void addMI(PMenuItem mi);	// Добавить элемент в блок
	
	// Скрыть/отобразить блок
	void hide();
	void show();
private:
	PMenuItem * m_block;	// Блок пунктов меню

	size_t m_size;	// Размер блока
	size_t m_pos;	// Позиция для нового элемента

	bool m_bVisible; // Видим ли блок
};