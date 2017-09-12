#ifndef TreasureSeeker_H
#define TreasureSeeker_H
#include "GamePiece.h"
#include "Player.h"
#include "Enemy.h"
#include "Trap.h"
#include "Treasure.h"
#include <fstream>

class TreasureSeeker
{
private:
	Player player;
	Enemy *enemies = NULL;
	Trap *traps = NULL;
	Treasure treasure;
	GamePiece GP;
	GamePiece *board[9][9];
	int NumOfEnemies = 0;
	int NumOfTraps = 0;
	void SetPlayer(); //Set player on board
	void SetTreasure(); //Set Treasure on board
	void SetEnemies(); //Set Enemies on board
	void SetTraps(); //Set traps on board
	void AddEnemy(int x, int y); //Add Enemy to array
	void KillEnemy(int i); //remove enemy from array
	bool Step(); //manage every step of the player
	void AddTrap(int x, int y); //Add trap to array
	void RemoveTrap(int index); //remove trap from array
	void UpdateBoard(); //Update all game pieces on board
	void ShowDataInFile(); //Show data from file
	void PrintBoard(); //print the board
public:
	void Play(); //start play the game
	void Save(ofstream& OutFile); //save to file
	void Open(ifstream& Infile); //load from file
	void NewGame(); //start's new game
	TreasureSeeker();
	~TreasureSeeker();
};

#endif
