#ifndef Enemy_H
#define Enemy_H
#include "GamePiece.h"

class Enemy : public GamePiece
{
public:
	string GetName(){ return default; }; //Get the class name "Enemy"
	char GetChar(){ return Default; }; //Get the class char "E"
	void Move(int PX, int PY);
	int SetTrap();
	Enemy();
	Enemy(int x, int y);
	Enemy(const Enemy& other);

};

#endif