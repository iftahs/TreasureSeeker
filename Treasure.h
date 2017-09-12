#ifndef Treasure_H
#define Treasure_H
#include "GamePiece.h"

class Treasure : public GamePiece
{
private:
	bool dummy;
public:
	string GetName(){ return default; };
	char GetChar(){ return Default; };
	void PrintTreasure();
	Treasure();
	Treasure(int x, int y);
	bool Dummy(){ return dummy; }; //50% the treasure is a dummy
	Treasure(const Treasure& other);
};

#endif
