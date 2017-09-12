#include "Treasure.h"

Treasure::Treasure(){
	int rnd = rand() % 2 + 1;
	if (rnd == 1)
		dummy = false;
	else
		dummy = true;
	this->default = "Treasure";
	this->Default = 'X';
}

Treasure::Treasure(int x, int y)
{
	Treasure();
	this->x = x;
	this->y = y;
	
}

Treasure::Treasure(const Treasure& other){
	Treasure();
	this->x = other.x;
	this->y = other.y;
}

void Treasure::PrintTreasure(){
	if (dummy == false)
		cout << "Congratulations – You WIN!" << endl;
	else
		cout << "The treasure was a fake! You LOSE!" << endl;
}