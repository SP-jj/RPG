// Name: Stef Pollo
// Date: 19 May 2021
// Program Name: 
// Purpose:

#include <iostream>
#include <fstream>
using namespace std;

int getValidInt()
{
	int x{};
	cin >> x;
	
	if(cin.fail())
	{
		cout << '\n' << "That entry is not a number. Please reenter a valid integer." << '\n';
		cin.clear();
		cin.ignore(10000,'\n');
		return getValidInt();
	}
	return x;
}

// check if countdown timer has reached 20 min
bool isTimeUp()
{
	string gameLogText;
	fstream gameLogFile;
	gameLogFile.open("../../gameLog", ios::in);
	if (!gameLogFile) {
		cout << "Error:No such file";
		return false;
	}
	else {

		// get last line in file
		while (! gameLogFile.eof()) {
			getline(gameLogFile,gameLogText);

		}
		gameLogFile.close();
		cout << gameLogText << '\n';

		// check if time is up
		if(gameLogText == "timeIsUp:True")
			return true;

		else if (gameLogText == "timeIsUp:False")
			return false;
		else
		{
			cout << "Error:Invalid input from file\n";
			return false;
		}
	}
}

// // hides a file or dir from the player
// void hideFile(string fileName)
// {
// 	string cmd { "mv "+fileName+" ."+fileName};
// 	system(cmd);
// }

// // shows a file or dir to the player
// void showFile(string fileName)
// {
// 	string cmd = "mv ."+fileName+" "+fileName;
// 	system(cmd);
// }

int makeDecision(string prompt, string options[], int numOfOptions)
{
	cout << '\n' << prompt << '\n';

	// display options to player
	for(int i{1} ; i < numOfOptions+1 ; i++)
	{
		cout << i << " - \t" << options[i-1] << '\n';
	}
	// validate player's choice
	int choice{ getValidInt()};
	while(choice < 1 || choice > numOfOptions)
	{
		cout << "You can only choose one of the given options. Please enter one of the numbers of the given paths.\n";
		choice = getValidInt();
	}

	// give confirmation msg for selected choice

	// index of selected choice from the options[] array
	return choice-1;
}

int main()
{


	
	if(isTimeUp())
	{
		cout << "\033[1;33mTime's up!!\n";
		cout << "You ran out of time while you were battling the Duke\033[0m\n";
		cout << "\033[1;31" << R"(
░██████╗░░█████╗░███╗░░░███╗███████╗  ░█████╗░██╗░░░██╗███████╗██████╗░
██╔════╝░██╔══██╗████╗░████║██╔════╝  ██╔══██╗██║░░░██║██╔════╝██╔══██╗
██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░██║╚██╗░██╔╝█████╗░░██████╔╝
██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗
╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ╚█████╔╝░░╚██╔╝░░███████╗██║░░██║
░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝
		)" <<  "\033[0m\n";
	}
	else
	{
		cout << "\033[1;32" << R"(
░█████╗░░█████╗░███╗░░██╗░██████╗░██████╗░░█████╗░████████╗██╗░░░██╗██╗░░░░░░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
██╔══██╗██╔══██╗████╗░██║██╔════╝░██╔══██╗██╔══██╗╚══██╔══╝██║░░░██║██║░░░░░██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
██║░░╚═╝██║░░██║██╔██╗██║██║░░██╗░██████╔╝███████║░░░██║░░░██║░░░██║██║░░░░░███████║░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
██║░░██╗██║░░██║██║╚████║██║░░╚██╗██╔══██╗██╔══██║░░░██║░░░██║░░░██║██║░░░░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
╚█████╔╝╚█████╔╝██║░╚███║╚██████╔╝██║░░██║██║░░██║░░░██║░░░╚██████╔╝███████╗██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
░╚════╝░░╚════╝░╚═╝░░╚══╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░░╚═════╝░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░                                                                                                              
		)" << "\033[0m\n";
		
	}

	return 0;
}
