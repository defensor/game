#pragma once

#include <vector>
#include "Item.h"
#include "global.h"

using namespace std;

typedef vector<Item> Items;

class NPC
{
public:
	NPC(string name, char tile, COORD coord);

	COORD getPosition()const;
	char getTile()const;
	string getName()const;

	void removeItem(short id);
	bool isItem(short id) const;
	void showSellerDialog(unsigned money);
	void showSmithDialog(const Items & playerItems, unsigned money)const;

	void setPosition(COORD coord);
private:
	COORD m_coord;

	char m_tile;
	string m_name;

public:
	vector<Item> m_items; //Товары
};