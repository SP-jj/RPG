// Name: Stef Pollo
// Date: 24 May 2021
// Program Name: approachTheMerchant.cpp
// Purpose: get 5 answers right in a row to win game with the merchant

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>

using namespace std;


// check if countdown timer has reached 20 min
bool isTimeUp()
{
	string gameLogText;
	fstream gameLogFile;
	gameLogFile.open("../../../../gameLog", ios::in);
	if (!gameLogFile) {
		cout << "Error:No such file";
		return false;
	}
	else {

		// get first line in file
		getline(gameLogFile,gameLogText);

		gameLogFile.close();
		//cout << gameLogText << '\n';

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

string gameOverAscii = R"(
░██████╗░░█████╗░███╗░░░███╗███████╗  ░█████╗░██╗░░░██╗███████╗██████╗░
██╔════╝░██╔══██╗████╗░████║██╔════╝  ██╔══██╗██║░░░██║██╔════╝██╔══██╗
██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░██║╚██╗░██╔╝█████╗░░██████╔╝
██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗
╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ╚█████╔╝░░╚██╔╝░░███████╗██║░░██║
░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝
		)";
string asciiMerchant { R"(
   .------\ /------.
   |       -       |
   |               |
   |               |
   |               |
_______________________
===========.===========
  / ~~~~~     ~~~~~ \
 /|     |     |\
 W   ---  / \  ---   W
 \.      |o o|      ./
  |                 |
  \    #########    /
   \  ## ----- ##  /
    \##         ##/
     \_____v_____/
)"};

const int GOAL_STREAK = 5;
const char OPERANDS[] { '+' , '-' , '/' , '*'};

// objective: get 5 math questions right in a row

class Game
{
	private:
		int streak;
	public:
		// generate random math question
		string generateQuestion()
		{
			// choose 2 random numbers from 1-50
			string num1 = to_string(( rand() % 50) + 1);
			string num2 = to_string(( rand() % 50) + 1);

			// choose a random math operand
			// for division, tell player to round down their answers
			char chosenOperand = OPERANDS[ ( rand() % 4) ];

			return num1 + chosenOperand + num2;

		}

		void quitGamePrompt()
		{
			while(true)
			{
				// check if player wants to quit game
				cin.clear();
				cin.ignore(10000,'\n');
				cout << "\x1b[33mAre you sure you want to quit the game? Your progress cannot be restored.\x1b[0m\n";	// yellow text
				cout << "Enter 'y' for Yes\t\t\tEnter 'n' for No\n";
				char choice{};
				cin >> choice;
				if(choice == 'y')
				{
					cout << "\n\n---- GAME OVER ----\n\n";
					exit(0);
				}
				else if(choice == 'n')
					break;
				
				cout << "You have to enter either 'y' or 'n'\n";

			}

		}

		// returns valid player answer
		int getPlayerAnswer(string question)
		{
			int ans{};
			cin >> ans;
			while(cin.fail())
			{
				// if player enters something other than an int, they might've been trying to quit the game
				quitGamePrompt();
				
				cout << "\nReminder that your answer should be a number rounded down to an integer.\n\n";
				cin.clear();
				cin.ignore(10000,'\n');

				cout << question << '\n';
				cin >> ans;
			}
			return ans;

		}

		int getSolution(string question)
		{
			char operand{};

			int num1{} , num2{} , operandIndex{};
			for (int i = 0; i < 4; i++)
			{
				if( (operandIndex = question.find( OPERANDS[i] ) ) != string::npos)
				{
					operand = OPERANDS[i];
					
					// num1 is substring from 0 to operand
					num1 = stoi( question.substr(0,operandIndex) );

					// num2 is substring from operand+1 to end
					num2 = stoi( question.substr(operandIndex+1) );

					// stoi() converts from string to int
					
					break;
				}
			}

			// cout << "operand: " << operand
			// 		<< "\nnum1: " << num1
			// 		<< "\nmun2: " << num2 << '\n';

			// calculate answer
			switch(operand)
			{
				case '*':
					return num1 * num2;
				case '/':
					return num1 / num2;
				case '-':
					return num1 - num2;
				case '+':
					return num1 + num2;
				default:
					return 404;
			}
		}

		Game()
		{

			cout << "\n\nEnter your answer (rounded down to an integer) after the question appears.\n";
			cout << "\nTo quit the game, enter anything other than an integer(Ex. decimal, letter, word, symbol, etc.)\n";
			cout << "\nBEGIN...\n";

			streak = 0;

			while (streak < 5)
			{
				cout << "\n~~~ CURRENT STREAK: " << streak << " ~~~\n\n";

				string question { generateQuestion() };

				cout << question <<'\n';

				int playerAns { getPlayerAnswer(question) };

				int solution { getSolution(question) };

				cout << "solution: " << solution << '\n';
				cout << "player ans: " << playerAns << '\n';

				if( solution == playerAns )
				{
					streak++;
					cout << "\x1b[32mCorrect!!!\x1b[0m\n";		// green text
				}

				else
				{
					streak = 0;
					cout << "\x1b[31mIncorrect.\x1b[0m\n";		// red text
				}
					
			}

			cout << "\n~~~ CURRENT STREAK: " << streak << " ~~~\n\n";
			cout << "-------- WE HAVE A WINNER --------\n";


		}

};


int main()
{
	srand(time(nullptr));

	cout << asciiMerchant << R"(
|"""""""""""""""""""""""""""""""""|
| Hello there, young fella!       |
| What can I do for you today?    |
 """""""""""""""""""""""""""""""""
	)" << '\n';

	usleep(1000000);

	cout << asciiMerchant << R"(
|"""""""""""""""""""""""""""""""""|
| Ohh, I see. You're here for     |
| information, like everyone else.|
| You want to know which crops are|
| going to be most in demand this |
| summer.                         |
 """""""""""""""""""""""""""""""""
	)" << '\n';

	usleep(3000000);

	cout << asciiMerchant << R"(
|"""""""""""""""""""""""""""""""""|
| Well, it's not gonna be free.   |
| That information is worth alot, |
| I think. Alothough, I do have   |
| something in mind you can       |
| exchange for it...              |
 """""""""""""""""""""""""""""""""
	)" << '\n';

	usleep(2000000);


	cout << asciiMerchant << R"(
|"""""""""""""""""""""""""""""""""|
| During my travels, I came across|
| an interesting, magical         |
| contraption. It is a container  |
| which can only be opened by     |
| answering five of it's questions|
| in a row correctly.             |
 """""""""""""""""""""""""""""""""
	)" << '\n';

	usleep(2000000);


	cout << asciiMerchant << R"(
|"""""""""""""""""""""""""""""""""|
| In exchange for opening this box|
| for me, I will grant you the    |
| information you seek.           |
 """""""""""""""""""""""""""""""""
	)" << '\n';

	usleep(1000000);


	//Game game;

	if(isTimeUp())
	{
		cout << "\033[31mTime's up!!\n";
		cout << "You ran out of time while you were talking to the merchant.\n";
		cout << "Now the transport has arrived to take you to the dungeons.\033[0m\n";
		cout << gameOverAscii <<  '\n';
	}
	else
	{
		cout << asciiMerchant << R"(
|"""""""""""""""""""""""""""""""""|
| Wow, thank you, M'boy!          |
| Well, a deal's a deal, so here  |
| you go...                       |
|                                 |
 """""""""""""""""""""""""""""""""
	)" << '\n';
		usleep(500000);
		cout << "...\n";
		usleep(500000);
		cout << "...\n";
		usleep(500000);
		cout << "...\n";
		usleep(500000);
		cout << "...\n";
		usleep(500000);
		cout << "...\n";

		cout << "\033[32mWoah, you're on a roll!!\n";
		cout << "Congrats! You've just completed your second task.\n\n";
		cout << "Onward to your final task... the Duke's manor!\033[0m\n";
		system("mv ../.DUKES_MANOR ../DUKES_MANOR");
	}

	return 0;
}