#include "MenuItem.h"
#include <string>
#include <conio.h>

// ������� ��������� ����� ������
void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

// ����������� �������� ��� ��������� �������� ����
MenuItem::MenuItem(int id, string text, COORD pos, bool dropDown, bool visible, bool selected, bool active,
	ConsoleColor activeTxtClr, ConsoleColor inactiveTxtClr, ConsoleColor bkClrOfSelectedItem,
	MenuItem * pNext, MenuItem * pPrev, MenuItem * pParent, MenuItem * pChild, MenuBlock * block, void(*pFunc)()) :
	m_id(id), m_szText(text), m_pos(pos), m_bDropDown(dropDown), m_bVisible(visible), m_bSelected(selected), m_bActive(active),	// �������� ���������
	m_activeTxtClr(activeTxtClr), m_inactiveTxtClr(inactiveTxtClr), m_bkClrOfSelectedItem(bkClrOfSelectedItem),					// �����
	m_pNext(pNext), m_pPrev(pPrev), m_pParent(pParent), m_pChild(pChild), m_menuBlock(block), m_pFunc(pFunc){	// ���������
}

//MenuItem::MenuItem(MenuItem & rhs){
//	m_id = rhs.getId();
//	m_szText = rhs.getStr();
//	m_pos = rhs.getPos();
//	m_bDropDown = rhs.isDropDown();
//	m_bVisible = rhs.isVisible();
//	m_bSelected = rhs.isSelected();
//	m_bActive = rhs.isActive();
//	m_activeTxtClr = rhs.getActiveTxtClr();
//	m_inactiveTxtClr = rhs.getInactiveTxtClr();
//	m_bkClrOfSelectedItem = rhs.getBkClrOfSlctdItem();
//	m_pNext = rhs.getNext();
//	m_pPrev = rhs.getNext();
//	m_pParent = rhs.getParent();
//	m_pChild = getChild();
//	m_pFunc = NULL/*getFunc()*/;
//}

int MenuItem::getId()const{
	return m_id;
}

string MenuItem::getStr()const{
	return m_szText;
}

COORD MenuItem::getPos()const{
	return m_pos;
}

ConsoleColor MenuItem::getActiveTxtClr()const{
	return m_activeTxtClr;
}

ConsoleColor MenuItem::getInactiveTxtClr()const{
	return m_inactiveTxtClr;
}

ConsoleColor MenuItem::getBkClrOfSlctdItem()const{
	return m_bkClrOfSelectedItem;
}

void (*MenuItem::getFunc()const)(){
	return m_pFunc;
}

ConsoleColor MenuItem::getTxtClr()const{
	if (m_bActive)
		return m_activeTxtClr;
	else
		return m_inactiveTxtClr;
}

ConsoleColor MenuItem::getBkClr()const{
	if (m_bSelected)
		return m_bkClrOfSelectedItem;
	else
		return Black;
}



string MenuItem::getText()const{
	if (m_bDropDown)
		return m_szText + ">";
	else
		return m_szText;
}

// ������� ��������� �������� ���� � �������
void MenuItem::print()const{
	if (!m_bVisible) // ���� ������� �������
		return;

	// ���������� ������� ��������� ������
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);	// �������� �����
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;		
	GetConsoleScreenBufferInfo(hConsoleHandle, &consoleScreenBufferInfo);	// �������� ��������� � ����������� � ������
	ConsoleColor oldTxtClr = (ConsoleColor)(BYTE)(consoleScreenBufferInfo.wAttributes & 0x0F), 
		oldBkClr = (ConsoleColor)(BYTE)((consoleScreenBufferInfo.wAttributes & 0xF0) >> 4);

	// ��������� ����� ��� ������� ������ ����
	SetColor(getTxtClr(), getBkClr());
	
	// ����������� �������
	SetConsoleCursorPosition(hConsoleHandle, m_pos);

	// ����� ������ ������� ������ ����
	printf("%s", getText().c_str());

	SetColor(oldTxtClr, oldBkClr);	// �������������� �����
}

MenuItem * MenuItem::goNext(){
	deselect();
	getNext()->select();
	return getNext();
}

MenuItem * MenuItem::goPrev(){
	deselect();
	getPrev()->select();
	return getPrev();
}

MenuItem * MenuItem::drop(){
	if (isDropDown() && isActive())
	{
		deselect();
		
		// ������ �������� ������� ����������� ����
		/*MenuItem * pParent = this;
		MenuItem * pFirstMI = getChild();
		bool cicleFlag = false;*/

		//for (MenuItem * p = getChild(); p != pParent; p = p->getNext()){	// �������� ��� �������� �������
		//	p->show();

		//	if (p == pFirstMI && cicleFlag)
		//		break;
		//	else if (p == pFirstMI)
		//		cicleFlag = true;
		//}

		getChild()->m_menuBlock->show();



		getChild()->select();
		return getChild();
	}

	return this;
}

MenuItem * MenuItem::compress(){
	if (getParent() != 0){
		deselect();

		//MenuItem * pParent = getParent();
		//MenuItem * pFirstMI = getParent()->getChild();
		//bool cicleFlag = false;
		//for (MenuItem * p = getParent()->getChild(); p != pParent; p = p->getNext()){	// �������� ��� �������� �������
		//	p->hide();
		//	
		//	if (p == pFirstMI && cicleFlag)
		//		break;
		//	else if (p == pFirstMI)
		//		cicleFlag = true;
		//}
		m_menuBlock->hide();

		getParent()->select();
		return getParent();
	}
	
	return this;
}


MenuItem * MenuItem::getParent()const{
	return m_pParent;
}

MenuItem * MenuItem::getChild()const{
	return m_pChild;
}

MenuItem * MenuItem::getNext()const{
	return m_pNext;
}

MenuItem * MenuItem::getPrev()const{
	return m_pPrev;
}

MenuBlock * MenuItem::getBlock()const{
	return m_menuBlock;
}

void MenuItem::setId(int id){
	m_id = id;
}

void MenuItem::setTxt(string txt){
	m_szText = txt;
}

void MenuItem::setPos(COORD pos){
	m_pos = pos;
}

void MenuItem::setParent(MenuItem * pParent){
	m_pParent = pParent;
}

void MenuItem::setChild(MenuItem * pChild){
	m_pChild = pChild;
}

void MenuItem::setNext(MenuItem * pNext){
	m_pNext = pNext;
}

void MenuItem::setPrev(MenuItem * pPrev){
	m_pPrev = pPrev;
}

void MenuItem::setBlock(MenuBlock * block){
	m_menuBlock = block;
}

void MenuItem::activate(){
	m_bActive = true;
}

void MenuItem::deactivate(){
	m_bActive = false;
}

void MenuItem::show(){
	m_bVisible = true;
}

void MenuItem::hide(){
	m_bVisible = false;
}

void MenuItem::select(){
	m_bSelected = true;
}

void MenuItem::deselect(){
	m_bSelected = false;
}

void MenuItem::action(){
	if (!m_bDropDown && m_bActive)
		m_pFunc();
}

bool MenuItem::isActive()const{
	return m_bActive;
}

bool MenuItem::isDropDown()const{
	return m_bDropDown;
}

bool MenuItem::isVisible()const{
	return m_bVisible;
}

bool MenuItem::isSelected()const{
	return m_bSelected;
}

// templ	  - ������ ������� ����
// names	  - ������ ���������� ������� ����
// num		  - ����� ������� ����
// start	  - ���������� ������� ������ ����
// step		  - ��� ����� �������� ����
// orientVert - true(������������ ����)/false(��������������) ��� ������������ ����� ��������
// canBack	  - �������� �� ������� �� ���� �� ��������, ���������������� �������� �����������
int ChoiceMenu(MenuItem templ, string * names, size_t num, COORD start, COORD step, bool orientVert, bool canBack){
	// �������� ����������� ������
	PMenuItem * miChoice = new PMenuItem[num];
	for (int i = 0; i < num; i++){
		miChoice[i] = new MenuItem(templ);
		miChoice[i]->setId(i);
		miChoice[i]->setTxt(names[i]);
		miChoice[i]->setPos({ start.X + (i*step.X), start.Y + (i*step.Y) });
	}

	// ��������� ������ ����� �����
	for (int i = 0; i < num; i++)
	{
		if (i > 0)
			miChoice[i]->setPrev(miChoice[i - 1]);
		else
			miChoice[i]->setPrev(miChoice[num - 1]);

		if (i < num - 1)
			miChoice[i]->setNext(miChoice[i + 1]);
		else
			miChoice[i]->setNext(miChoice[0]);
	}

	// ������������ ������ �������
	miChoice[0]->select();

	// �������� �� ������� ����� ����
	PMenuItem pMI = miChoice[0];

	// ���� ����
	bool exitFlag = 0;
	while (!exitFlag){

		// ��������� ����
		for (int i = 0; i < num; i++)
			miChoice[i]->print();

		// ��������� �������
		int code = _getch();

		if (code == 0 || code == 224)	// ���� ������ ������ ���������
			code = _getch();			// �� ������ ������������ ������

		// ������ ������� �������
		switch (code){
		case BTN_ESC:	// Esc
			delete[] miChoice;		// ������� �� ������������� ��������
			return -1;
			break;
		case BTN_ENTER:	// Enter
			exitFlag = true;		// ����� ������, ��������� ���� ����
			break;

		case BTN_UP:	// �����
			if (orientVert)		// ���� ���� ������������
				pMI = pMI->goPrev();	// ��������� � ����������� ��������
			else if (canBack){	// ���� �� ������������ � �������� ������� �� ���� �� ��������
				delete[] miChoice;
				return -1;		// �� ����������� ����
			}
			break;

		case BTN_DOWN:	// ����
			if (orientVert)		// ���� ���� ������������
				pMI = pMI->goNext();	// ��������� � ��������� ��������
			else if (canBack){	// ���� �� ������������ � �������� ������� �� ���� �� ��������
				delete[] miChoice;
				return -1;		// �� ����������� ����
			}
			break;

		case BTN_LEFT:	// �����
			if (!orientVert)		// ���� ���� ���������������
				pMI = pMI->goPrev();	// ��������� � ����������� ��������
			else if (canBack){	// ���� ������������ � �������� ������� �� ���� �� ��������
				delete[] miChoice;
				return -1;		// �� ����������� ����
			}
			break;

		case BTN_RIGHT:	// ������
			if (!orientVert)		// ���� ���� ���������������
				pMI = pMI->goNext();	// ��������� � ��������� ��������
			else if (canBack){	// ���� ������������ � �������� ������� �� ���� �� ��������
				delete[] miChoice;
				return -1;		// �� ����������� ����
			}
			break;
		}
	}

	// �������� ����� ���������� ��������
	int id = pMI->getId();

	// ������� ������ ���������� ��� ����
	delete[] miChoice;

	return id;
}
/////////////////////////////////////////////////////////////////////////////////////////////
MenuBlock::MenuBlock(size_t size, PMenuItem * block){
	m_block = new PMenuItem[size];
	
	for (int i = 0; i < size; i++)
		m_block[i] = block[i];

	m_pos = size;
	m_size = size;
}

MenuBlock::MenuBlock(size_t size){
	m_block = new PMenuItem[size];

	m_pos = 0;
	m_size = size;
}

MenuBlock::~MenuBlock(){
	if (m_block != NULL)
		delete[] m_block;
}

bool MenuBlock::getVisible()const{
	return m_bVisible;
}

void MenuBlock::setVisible(bool visible){
	m_bVisible = visible;
}

void MenuBlock::addMI(PMenuItem mi){
	if (m_pos < m_size)
		m_block[m_pos++] = mi;
}

void MenuBlock::hide(){
	m_bVisible = false;

	for (int i = 0; i < m_pos; i++)
		m_block[i]->hide();
}

void MenuBlock::show(){
	m_bVisible = true;

	for (int i = 0; i < m_pos; i++)
		m_block[i]->show();
}