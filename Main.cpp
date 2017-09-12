
#include "TreasureSeeker.h"
#include <ostream>
using namespace std;

void SaveGame(TreasureSeeker&); //Saving the game to binary file
void OpenGame(TreasureSeeker&); //Open game from binary file
void ShowManu(int kind, TreasureSeeker& Game);

int main(){
	TreasureSeeker Game;
	cout << "Wellcome to Treasure Seeker game. Please select from manu:" << endl;
	ShowManu(0, Game);
	return 0;
}

void ShowManu(int kind, TreasureSeeker& Game){
	if (kind == 0){
		cout << "1. Start new game" << endl
			<< "2. Load game" << endl
			<< "3. Exit" << endl;
		int select;
		do{
			cin.clear();
			fflush(stdin);
			cin >> select;
			switch (select)
			{
			case 1:
				Game.NewGame(); //Start's new game
				Game.Play(); //Player the game
				ShowManu(1, Game);
				break;
			case 2:
				OpenGame(Game);
				Game.Play();
				ShowManu(1, Game);
				break;
			case 3:
				Game.~TreasureSeeker();
				break;
			default:
				break;
			}
		} while (select < 1 || select > 3);
	}
	else if (kind == 1){
			cout << "1. Start new game" << endl
			<< "2. Save Game" << endl
			<< "3. Exit" << endl;
		int select;
		do{
			cin.clear();
			fflush(stdin);
			cin >> select;
			switch (select)
			{
			case 1:
				Game.NewGame();
				Game.Play();
				ShowManu(1, Game);
				break;
			case 2:
				SaveGame(Game);
				ShowManu(1, Game);
				break;
			case 3:
				return;
				break;
			default:
				break;
			}
		} while (select < 1 || select > 3);
	}
}

void SaveGame(TreasureSeeker &Game){
	string FileName = "data.bin";
	ofstream outFile(FileName, ios::binary | ios::trunc); //Open file for writing
	
	if (outFile.fail())
		cout << "Unable to save game." << endl;
	else{
		Game.Save(outFile);
		cout << "Game Saved!" << endl;
	}
	outFile.close();
}

void OpenGame(TreasureSeeker &Game){
	string FileName = "data.bin";
	ifstream inFile(FileName, ios::binary | ios::in); //Open file for reading
	if (inFile.fail()){
		cout << "Unable to open the file." << endl;
		Game.~TreasureSeeker();
		exit(1);
	}
	else
		Game.Open(inFile);
	inFile.close();
}