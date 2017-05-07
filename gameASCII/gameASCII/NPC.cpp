#include <iostream>
#include <string>
#include <conio.h>
#include "NPC.h"


NPC::NPC(char tile) :
_tile(tile)
{
	switch (_tile)
	{
	case SELLER_TILE: _name = "Seller";
		break;
	case SMITH_TILE: _name = "Koval"; 
		break;
	}
}

void NPC::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

Item NPC::gettingItem(short id)
{
	Item item = _items.at(id);
	_items[id] = _items.back();
	_items.pop_back();
	return item;
}

bool NPC::isItem(short id) const
{
	return ((id >= 0) && (id < _items.size()))? true:false;
}

void NPC::showSellerDialog(unsigned money)
{
	int itemVal = _items.size();
	system("CLS");
	cout << "Money: " << money << endl;
	cout << this->_name << endl << endl;
	cout << this->_name << " have " << itemVal << " items." << endl;
	if (itemVal > 0)
		cout << "\tNAME\tPRICE\tDMG\tDEF" << endl;
	for (int j = 0; j < itemVal; j++)
		cout << j + 1 << ".\t" << _items.at(j).getName() << "\t" << _items.at(j).getPrice() << "\t" << _items.at(j).getDamage() * 100 << "%\t" << _items.at(j).getDefense() * 100 << "%" << endl;
	cout << "0. Exit.";
}

void NPC::showSmithDialog(Items items, unsigned money)
{
	int itemVal = items.size();
	int count = 0;
	
	system("CLS");
	cout << "Money: " << money << endl;
	cout << this->_name << endl << endl;
	cout << this->_name << " can upgrade your items." << endl;
	
	bool isUpgradebleItem = false;
	for (int i = 0; i < itemVal && !isUpgradebleItem; i++)
		if (items[i].getLevel() < 10)
			isUpgradebleItem = true;

	if (isUpgradebleItem)
		cout << "\tNAME\tLEVEL\tPRICE\tCUR DMG\tCUR DEF\tUP DMG\tUP DEF" << endl;
	for (vector<Item>::const_iterator ci = items.begin(); ci < items.end(); ci++)
		if (ci->getLevel() < 10)
			cout << ++count << ".\t" << ci->getName() << "\t" << ci->getLevel() <<"\t" << ci->getUpdatePrice() << "\t" << ci->getDamage()*100 << "%\t" << ci->getDefense()*100 << "%\t" << (ci->getDamage() + ci->getDamageUpdateDifference())*100 << "%\t" << (ci->getDefense() + ci->getDefenceUpdateDifference())*100 << "%" << endl;
	cout << "0. Exit.";
}