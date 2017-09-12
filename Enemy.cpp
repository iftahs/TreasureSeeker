#include "Enemy.h"

Enemy::Enemy(){
	this->default = "Enemy";
	this->Default = 'E';
}

Enemy::Enemy(int x, int y)
{
	Enemy();
	this->x = x;
	this->y = y;
}

Enemy::Enemy(const Enemy& other){
	Enemy();
	this->x = other.x;
	this->y = other.y;
}

void Enemy::Move(int PX, int PY){
	int disx, disy;
	disx = abs(this->x - PX);
	disy = abs(this->y - PY);
	if (disx > disy){
		if (PX < this->x)
			(this->x)--;
		else
			(this->x)++;
	}
	else if (disx < disy){
		if (PY < this->y)
			(this->y)--;
		else
			(this->y)++;
	}
	else if (disx == disy){
		if (PX < this->x)
			(this->x)--;
		else
			(this->x)++;
	}
}

int Enemy::SetTrap(){
	int success = rand() % 4 + 1;
	if (success == 1){
		cout << "Watch out!Enemy successfully planted a trap!" << endl;
		return 1;
	}
	else{
		int boom = rand() % 20 + 1;
		if (boom == 1){
			cout << "Enemy died from a trap!" << endl;
			return -1;
		}
		else
			return 0;
	}
}