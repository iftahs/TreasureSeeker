#include "TreasureSeeker.h"

TreasureSeeker::TreasureSeeker(){
	srand(time(NULL)); //For random functions
}

TreasureSeeker::~TreasureSeeker()
{
	delete[] enemies;
	delete[] traps;
}

//Start's a new game
void TreasureSeeker::NewGame(){
	player = Player();
	NumOfEnemies = 0;
	NumOfTraps = 0;

	cout << "Please enter your name: ";
	string name;
	cin >> name;
	player.SetName(name);
	cout << endl << "INSTRUCTIONS:" << endl << "You need to go to the treasure without meet the enemies or step on a trap." << endl
		<< "If you meet an enemy you can fight him with your throwing knifes. You got 50% chance to kill the enemy or die." << endl
		<< "If you step on a trap you can try to disarm the trap. You got 25% chance to disarm the trap. Otherwise you will die." << endl
		<< "On every step you got 5% chance to find a new knife, but also 5% chance for new enemy to appear." << endl
		<< "On every enemy step he got 25% to plant a new trap. If he faild, he got 5% chance to die from the trap." << endl
		<< endl << "Ok " << name << ". Game Started!" << endl << endl;
	SetPlayer(); //Put Player on board
	SetTraps(); //Put traps on board
	SetTreasure(); //Put treasure on board
	SetEnemies(); //put enemies on board
	UpdateBoard(); //Update all field of board
}

//Open binary file and read data from it.
void TreasureSeeker::Open(ifstream& Infile){
	Infile.read((char*)&player, sizeof(player));
	Infile.read((char*)&treasure, sizeof(treasure));
	Infile.read((char*)&NumOfEnemies, sizeof(NumOfEnemies));
	Infile.read((char*)&NumOfTraps, sizeof(NumOfTraps));
	enemies = new Enemy[NumOfEnemies];
	Infile.read(reinterpret_cast<char*>(enemies), NumOfEnemies*sizeof(Enemy));
	traps = new Trap[NumOfTraps];
	Infile.read(reinterpret_cast<char*>(traps), NumOfTraps*sizeof(Trap));
	UpdateBoard();
	//ShowDataInFile();
}

//Help method only to show data from file. Not include in the game itself.
void TreasureSeeker::ShowDataInFile(){
	cout << "Player: x=" << player.GetX() << " y=" << player.GetY() << ", Name: " << player.GetPlayerName() << endl;
	cout << "Treasure: x=" << treasure.GetX() << " y=" << treasure.GetY() << endl;
	cout << "Number Of Enemies: " << NumOfEnemies << endl;
	for (int i = 0; i < NumOfEnemies; i++)
		cout << "Enemy " << i+1 << ": x=" << enemies[i].GetX() << ", y=" << enemies[i].GetY() << endl;
	cout << "Number Of Traps: " << NumOfTraps << endl;
	for (int i = 0; i < NumOfTraps; i++)
		cout << "Trap " << i+1 << ": x=" << traps[i].GetX() << ", y=" << traps[i].GetY() << endl;
}

//Save the game to binary file.
void TreasureSeeker::Save(ofstream& OutFile){
	OutFile.write((const char*)&player, sizeof(player));
	OutFile.write((const char*)&treasure, sizeof(treasure));
	OutFile.write((const char*)&NumOfEnemies, sizeof(NumOfEnemies));
	OutFile.write((const char*)&NumOfTraps, sizeof(NumOfTraps));
	OutFile.write(reinterpret_cast<const char*>(enemies), NumOfEnemies*sizeof(Enemy));
	OutFile.write(reinterpret_cast<const char*>(traps), NumOfTraps*sizeof(Trap));
}

//Print's the board to the screen
void TreasureSeeker::PrintBoard(){
	for (int i = 0; i < 70; i++)
		cout << "-";
	cout << endl;
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			cout << "[" << board[i][j]->GetChar() << "] ";
		}
		if (i == 0)
			cout << "\tPlayer Name: " << player.GetPlayerName();
		if (i == 1)
			cout << "\tYou killed " << player.GetKills() << " enemies.";
		if (i == 2)
			cout << "\tYou disarmed " << player.GetTrapsN() << " traps.";
		if (i == 3)
			cout << "\t" << player.GetKnifes() << " knifes available.";
		if (i == 4)
			cout << "\tPress 0 to show manu.";
		if (i == 5)
			cout << "\tPlayer: P";
		if (i == 6)
			cout << "\tTreasure: X";
		if (i == 7)
			cout << "\tTrap: T";
		if (i == 8)
			cout << "\tEnemy: E";
		cout << endl;
	}
	for (int i = 0; i < 70; i++)
		cout << "-";
	cout << endl;
}

//Set player X and Y coordinates
void TreasureSeeker::SetPlayer(){
	//Set random corner
	int x = rand() % 2 + 1;
	int y = rand() % 2 + 1;
	if (x == 1)
		x = 0;
	else
		x = 8;
	if (y == 1)
		y = 0;
	else
		y = 8;
	player.SetX(x);
	player.SetY(y);
}

//Set 1 to 3 traps on board
void TreasureSeeker::SetTraps(){
	bool OnPlayer = false;
	int x, y;
	//Set number of traps between 1 to 3
	int count = rand() % 3 + 1;
	
	for (int i = 0; i < count; i++){
		do{
			x = rand() % 8;
			y = rand() % 8;

			if (x == player.GetX() && y == player.GetY())
				OnPlayer = true;
			else
				OnPlayer = false;
		} while (OnPlayer == true);
		AddTrap(x, y);
	}
}

//Add trap to traps array
void TreasureSeeker::AddTrap(int x, int y){
	if (NumOfTraps == 0){
		traps = new Trap[1];
		traps[0].SetX(x);
		traps[0].SetY(y);
	}
	else if (NumOfTraps > 0){
		Trap *Temp = new Trap[NumOfTraps];
		for (int i = 0; i < NumOfTraps; i++){
			Temp[i] = traps[i];
		}
		traps = new Trap[NumOfTraps + 1];
		for (int i = 0; i < NumOfTraps; i++){
			traps[i] = Temp[i];
		}
		traps[NumOfTraps].SetX(x);
		traps[NumOfTraps].SetY(y);
		delete[] Temp;
	}
	NumOfTraps++;
}

//Set the treasure on the board
void TreasureSeeker::SetTreasure(){
	bool blank = true;
	int x, y;
	do{
		x = rand() % 8;
		y = rand() % 8;
		if (x == player.GetX() && y == player.GetY()){
			blank = false;
		}
		else{
			for (int i = 0; i < NumOfTraps; i++){
				if (x == traps[i].GetX() && y == traps[i].GetY()){
					blank = false;
					break;
				}
				blank = true;
			}
			if (blank == true){
				treasure.SetX(x);
				treasure.SetY(y);
			}
		}
	} while (blank == false);
}

//Set enemies on the board
void TreasureSeeker::SetEnemies(){
	bool blank = true;
	int x, y;
		do{
			x = rand() % 8;
			y = rand() % 8;
			if (x == player.GetX() && y == player.GetY() || x == treasure.GetX() && y == treasure.GetY())
				blank = false;
			else if ((abs(player.GetX() - x) < 3 || abs(player.GetY() - y) < 3)){
				blank = false;
			}
			else{
				blank = true;
				AddEnemy(x, y);
			}
		} while (blank == false);
}

//Add enemy to enemeis array
void TreasureSeeker::AddEnemy(int x, int y){
	if (NumOfEnemies == 0){
		enemies = new Enemy[1];
		enemies[0].SetX(x);
		enemies[0].SetY(y);
	}
	else if (NumOfEnemies > 0){
		Enemy *Temp = new Enemy[NumOfEnemies];
		for (int i = 0; i < NumOfEnemies; i++){
			Temp[i] = enemies[i];
		}
		enemies = new Enemy[NumOfEnemies + 1];
		for (int i = 0; i < NumOfEnemies; i++){
			enemies[i] = Temp[i];
		}
		enemies[NumOfEnemies].SetX(x);
		enemies[NumOfEnemies].SetY(y);
		delete[] Temp;
	}
	NumOfEnemies++;
}

//remove enemie from array
void TreasureSeeker::KillEnemy(int index){
	Enemy *temp = new Enemy[NumOfEnemies - 1];
	for (int i = 0, j = 0; i < NumOfEnemies; i++){
		if (i != index){
			temp[j] = enemies[i];
			j++;
		}
		else
			enemies[i].~Enemy();
	}
	enemies = new Enemy[--NumOfEnemies];
	for (int i = 0; i < NumOfEnemies; i++)
		enemies[i] = temp[i];
	delete[] temp;
}

//Remove trap from array
void TreasureSeeker::RemoveTrap(int index){
	Trap *temp = new Trap[NumOfTraps - 1];
	for (int i = 0, j = 0; i < NumOfTraps; i++){
		if (i != index){
			temp[j] = traps[i];
			j++;
		}
		else
			traps[i].~Trap();
	}
	traps = new Trap[--NumOfTraps];
	for (int i = 0; i < NumOfTraps; i++)
		traps[i] = temp[i];
	delete[] temp;
}

//Manage every stap of the player
bool TreasureSeeker::Step(){
	if (player.Move() == 1) return false;
	
	//5% chance for new enemy
	int chance = rand() %20 + 1;
	if (chance == 1){
		SetEnemies();
		cout << "New enemy was born." << endl;
	}

	//Enemy Step
	for (int i = 0; i < NumOfEnemies; i++){
		if (player.GetX() == enemies[i].GetX() && player.GetY() == enemies[i].GetY()){
			if (!player.Fight())
				return false;
			else{
				KillEnemy(i);
				break;
			}
		}
		//25% Chance for enemy to set new trap.
		int setTrap = enemies[i].SetTrap();
		if (setTrap == 1)
			AddTrap(enemies[i].GetX(), enemies[i].GetY());
		else if (setTrap == -1){
			KillEnemy(i); //5% Enemy dies from trap
			break;
		}
		enemies[i].Move(player.GetX(), player.GetY());
		if (player.GetX() == enemies[i].GetX() && player.GetY() == enemies[i].GetY()){
			if (!player.Fight())
				return false;
			else{
				KillEnemy(i);
				break;
			}
		}
	}

	//Player Step On Trap
	for (int i = 0; i < NumOfTraps; i++){
		if (player.GetX() == traps[i].GetX() && player.GetY() == traps[i].GetY()){
			if (player.NeutralizTrap())
				RemoveTrap(i);
			else
				return false;
			
		}
	}

	//Player Find Treasure
	if (player.GetX() == treasure.GetX() && player.GetY() == treasure.GetY()){
		treasure.PrintTreasure();
		return false;
	}
	player.FindKnife();
	UpdateBoard();
	cout << endl;
	return true;
}

//Update all game pieces on board
void TreasureSeeker::UpdateBoard(){
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++){
			board[i][j] = &GP;
		}
	board[player.GetX()][player.GetY()] = &player;
	for (int i = 0; i < NumOfTraps; i++)
		board[traps[i].GetX()][traps[i].GetY()] = &traps[i];
	board[treasure.GetX()][treasure.GetY()] = &treasure;
	for (int i = 0; i < NumOfEnemies; i++)
		board[enemies[i].GetX()][enemies[i].GetY()] = &enemies[i];
}

//Manage the game.
void TreasureSeeker::Play(){
	bool goon = true;
	do{
		 PrintBoard();
		 goon = Step();
	} while (goon);
	cout << endl;
}