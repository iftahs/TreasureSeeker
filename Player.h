#include "GamePiece.h"

#ifndef Player_H
#define Player_H

class Player : public GamePiece
{
private:
	string PlayerName;
	int Knifes;
	int kills;
	int TrapsNeutraliz;
	void PrintSteps();
public:
	string GetName(){ return default; }; //Get's class name "Player"
	char GetChar(){ return Default; }; //Get's calss char "P"
	int GetKills(){ return kills; }; //Return number of enemy kills
	int GetKnifes(){ return Knifes; }; //Return number of knifes left.
	int GetTrapsN(){ return TrapsNeutraliz; }; //Number of traps Neutralized
	string GetPlayerName(){ return PlayerName; }; //Return Player name
	bool NeutralizTrap(); //When the player step on a trap he can neutralize it.
	bool Fight(); //When the player meet the enemy he can fight him if the got left throwin knifes.
	int Move(); //Manage wich dirction the player can go.
	void FindKnife(); //5% to find a new knife on every move
	void SetName(string name); //Get's player name
	Player();
	Player(int x, int y);
	Player(const Player& other);
};

#endif

