#include "Trap.h"

Trap::Trap(){
	this->default = "Trap";
	this->Default = 'T';
}

Trap::Trap(int x, int y){
	Trap();
	this->x = x;
	this->y = y;
}

Trap::Trap(const Trap& other){
	this->x = other.x;
	this->y = other.y;
	Trap();
}
