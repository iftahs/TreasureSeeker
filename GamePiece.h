#ifndef GamePiece_H
#define GamePiece_H

#include<iostream>
#include<string>
#include<ctime>


using namespace std;

class GamePiece
{
protected:
	string default;
	char Default;
	virtual int Move(){ return 0; };
	int x, y;
public:
	GamePiece();
	GamePiece(int x, int y);
	GamePiece(const GamePiece& other);
	virtual string GetName(){ return default; };
	virtual char GetChar(){ return Default; };
	int GetX(){ return x; };
	int GetY(){ return y; };
	void SetX(int x){ this->x = x; };
	void SetY(int y){ this->y = y; };
	virtual ~GamePiece(){};
};

#endif

