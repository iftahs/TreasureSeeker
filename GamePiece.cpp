#include "GamePiece.h"

GamePiece::GamePiece(){
	srand(time(NULL));
	default = "Empty";
	Default = ' ';
}

GamePiece::GamePiece(int x, int y)
{
	GamePiece();
	this->x = x;
	this->y = y;
}

GamePiece::GamePiece(const GamePiece& other){
	this->x = other.x;
	this->y = other.y;
	this->Default = other.Default;
	this->default = other.default;
}