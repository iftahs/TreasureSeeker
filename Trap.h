#ifndef Trap_H
#define Trap_H
#include "GamePiece.h"
class Trap : public GamePiece
{
public:
	string GetName(){ return default; };
	char GetChar(){ return Default; };
	Trap();
	Trap(int x, int y);
	Trap(const Trap& other);
};

#endif
