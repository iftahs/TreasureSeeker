#include "Player.h"

Player::Player(){
	this->default = "Player";
	this->Default = 'P';
	this->Knifes = 1;
	this->kills = 0;
	this->TrapsNeutraliz = 0;
}

Player::Player(int x, int y)
{
	Player();
	this->x = x;
	this->y = y;
}

Player::Player(const Player& other){
	this->x = other.x;
	this->y = other.y;
	this->Default = 'P';
	this->default = "Player";
	this->kills = other.kills;
	this->Knifes = other.Knifes;
	this->TrapsNeutraliz = other.TrapsNeutraliz;
	this->PlayerName = other.PlayerName;
}

bool Player::NeutralizTrap(){
	cout << "You can try to neutraliz the trap." << endl << "Please Select:" << endl << "1. Neutraliz trap." << endl << "2. Give Up!" << endl;
	int choose;
	do{
		cin >> choose;
		if (choose == 2){
			cout << "You step on a trap an died. Game over!" << endl;
			return false;
		}
		else if (choose == 1){
			int Succsess = rand() % 4 + 1;
			if (Succsess == 1){
				TrapsNeutraliz++;
				cout << "The trap was successfully removed." << endl << "Total traps removed: " << TrapsNeutraliz << endl;
				return true;
			}
			else{
				cout << "You faild to neutraliz the trap and died. Game Over!" << endl;
				return false;
			}
		}
		else
			cout << "Invalid Choice. Please enter again: ";
	} while (choose != 1 || choose != 0);
}

bool Player::Fight(){
	if (Knifes == 0){
		cout << "Out of knifes. You can't fight the enemy. Game Over!" << endl;
		return false;
	}
	else{
		int success = rand() % 2 + 1;
		if (success == 1){
			cout << "You killed the enemy!" << endl;
			Knifes--;
			kills++;
			cout << "Total Enemies killed by you: " << kills << endl << "Total knifes left: " << Knifes << endl;
			return true;
		}
		else{
			cout << "You killed by the enemy. Game over." << endl;
			return false;
		}
	}
}

void Player::PrintSteps(){
	//Show Avaliable steps
	if (this->x == 0 && this->y != 0 && this->y != 8)
		cout << "Choose your Step:" << endl << "1. Down | 3. Left | 4. Right | 0. Manu" << endl;
	else if (this->x == 8 && this->y != 0 && this->y != 8)
		cout << "Choose your Step:" << endl << "2. Up | 3. Left | 4. Right | 0. Manu" << endl;
	else if (this->y == 0 && this->x != 0 && this->x != 8)
		cout << "Choose your Step:" << endl << "1. Down | 2. Up | 4. Right | 0. Manu" << endl;
	else if (this->y == 8 && this->x != 0 && this->x != 8)
		cout << "Choose your Step:" << endl << "1. Down | 2. Up | 3. Left | 0. Manu" << endl;
	else if (this->x == 0 && this->y == 0)
		cout << "Choose your Step:" << endl << "1. Down | 4. Right | 0. Manu" << endl;
	else if (this->x == 0 && this->y == 8)
		cout << "Choose your Step:" << endl << "1. Down | 3. Left | 0. Manu" << endl;
	else if (this->x == 8 && this->y == 0)
		cout << "Choose your Step:" << endl << "2. Up | 4. Right | 0. Manu" << endl;
	else if (this->x == 8 && this->y == 8)
		cout << "Choose your Step:" << endl << "2. Up | 3. Left | 0. Manu" << endl;
	else
		cout << "Choose your Step:" << endl << "1.Down | 2. Up | 3. Left | 4. Right | 0. Manu" << endl;
}

int Player::Move(){
	PrintSteps();
	bool ValidStep;
	do{
		cin.clear();
		fflush(stdin);
		int dir;
		cin >> dir;
		switch (dir)
		{
		case 0:
			return 1;
			ValidStep = false;
			break;
		case 1:
			if (this->x == 8)
				ValidStep = false;
			else{
				ValidStep = true;
				(this->x)++;
			}
			break;
		case 2:
			if (this->x == 0)
				ValidStep = false;
			else{
				ValidStep = true;
				(this->x)--;
			}
		break;
		case 3:
			if (this->y == 0)
				ValidStep = false;
			else{
				ValidStep = true;
				(this->y)--;
			}
			break;
		case 4:
			if (this->y == 8)
				ValidStep = false;
			else{
				ValidStep = true;
				(this->y)++;
			}
			break;
			default:
				ValidStep = false;
				break;
		}
		if (ValidStep == false && dir != 0)
			cout << "Invalid step. Please Enter again." << endl;
		if (dir == 0){
			cout << "The game was continued. Please select your step:" << endl;
			PrintSteps();
		}
	} while (ValidStep == false);
	return 0;
}

void Player::SetName(string name){
	this->PlayerName = name;
}

void Player::FindKnife(){
	int success = rand() % 20 + 1;
	if (success == 1){
		cout << "You found a knife." << endl;
		Knifes++;
		cout << "Total Knifes: " << Knifes << endl;
	}
}