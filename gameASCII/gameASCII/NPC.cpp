#include <iostream>
#include <string>
#include <conio.h>
#include "NPC.h"


NPC::NPC(string name, char tile, COORD coord){
	m_name = name;
	m_tile = tile;
	m_coord = coord;
}

void NPC::setPosition(COORD coord)
{
	m_coord = coord;
}

void NPC::removeItem(short id)
{
	m_items[id] = m_items.back();
	m_items.pop_back();
}

bool NPC::isItem(short id) const
{
	return ((id >= 0) && (id < m_items.size()))? true:false;
}

void NPC::showSellerDialog(unsigned money)
{
	int itemVal = m_items.size();
	system("CLS");
	cout << "Money: " << money << endl;
	cout << m_name << endl << endl;
	cout << m_name << " have " << itemVal << " items." << endl;
	if (itemVal > 0)
		cout << "\tNAME\tPRICE\tDMG\tDEF" << endl;
	for (int j = 0; j < itemVal; j++)
		cout << j + 1 << ".\t" << m_items.at(j).getName() << "\t" << m_items.at(j).getPrice() << "\t" << m_items.at(j).getDamage() << "\t" << m_items.at(j).getDefense() * 100 << "%" << endl;
	cout << "0. Exit.";
}

void NPC::showSmithDialog(const Items & playerItems, unsigned money)const{
	int itemVal = playerItems.size();
	int count = 0;
	
	system("CLS");
	cout << "Money: " << money << endl;
	cout << m_name << endl << endl;
	cout << m_name << " can upgrade your items." << endl;
	
	bool isUpgradebleItem = false;
	for (int i = 0; i < itemVal && !isUpgradebleItem; i++)
		if (playerItems[i].getLevel() < 10)
			isUpgradebleItem = true;

	if (isUpgradebleItem)
		cout << "\tNAME\tLEVEL\tPRICE\tCUR DMG\tCUR DEF\tUP DMG\tUP DEF" << endl;
	for (vector<Item>::const_iterator ci = playerItems.begin(); ci < playerItems.end(); ci++)
		if (ci->getLevel() < 10)
			cout << ++count << ".\t" << ci->getName() << "\t" << ci->getLevel() <<"\t" << ci->getUpdatePrice() << "\t" << ci->getDamage() << "\t" << ci->getDefense()*100 << "%\t" << (ci->getDamage() + ci->getDamageUpdateDifference()) << "\t" << (ci->getDefense() + ci->getDefenceUpdateDifference())*100 << "%" << endl;
	cout << "0. Exit.";
}

char NPC::getTile()const{ 
	return m_tile; 
}

string NPC::getName()const{ 
	return m_name; 
}
