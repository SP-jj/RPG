// Name: Stef Pollo
// Date: 19 May 2021
// Program Name: befriendTheSnake.cpp
// Purpose: get the snake 10 pieces of apples(in the snake game) to convince him not to eat the humans
// Resources: https://www.youtube.com/playlist?list=PL2C01CC54638DD952
#include <string>
#include <fstream>
#include "snake.h"

using namespace std;


// check if countdown timer has reached 20 min
bool isTimeUp()
{
	string gameLogText;
	fstream gameLogFile;
	gameLogFile.open("../../../../../gameLog", ios::in);
	if (!gameLogFile) {
		cout << "Error:No such file";
		return false;
	}
	else {

		// get first line in file
		getline(gameLogFile,gameLogText);
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


// so that the snakeGame obj only exists inside the function's scope,
// and is destrooyed when the game ends
int startGame()
{
	snakeClass s;

	if(s.start() == 1)
		return 1;
	return 0;
}


string gameOverAscii = R"(
░██████╗░░█████╗░███╗░░░███╗███████╗  ░█████╗░██╗░░░██╗███████╗██████╗░
██╔════╝░██╔══██╗████╗░████║██╔════╝  ██╔══██╗██║░░░██║██╔════╝██╔══██╗
██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░██║╚██╗░██╔╝█████╗░░██████╔╝
██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗
╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ╚█████╔╝░░╚██╔╝░░███████╗██║░░██║
░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝
		)";
string algernonAscii = R"(
      _______
     / _   _ \
    / (.) (.) \
   ( _________ )
    \`-V-|-V-'/
     \   |   /
      \  ^  /
       \    \
        \    `-_
         `-_    -_
            -_    -_
            _-    _-
          _-    _-
        _-    _-
      _-    _-
      -_    -_
        -_    -_
          -_    -_
            -_    -_
)";

int main()
{
	cout << algernonAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""""""|
| Psssssssssssssss. Why did you come here, human?|
| I will eat you,now.                            | 
 """"""""""""""""""""""""""""""""""""""""""""""""
	)";
	usleep(2000000);

	cout << algernonAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""""""""""""""""|
| What's thissss? You're already bargainging for your life?|
| Well, there's no usssse. I would never make any deal     |
| with a lowly hu--Wait, did you sssssay applesssssssss?   |
 """"""""""""""""""""""""""""""""""""""""""""""""""""""""""
	)";
	usleep(2000000);

	cout << algernonAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""""""""""""""""|
| Well... that isssss a deal worth considering. Hold on,   |
| so in exchange for aiding me in my quest for apples, you |
| don't just want me to spare your life, but also all the  |
| other human ssssscum that crosses my path?               |
 """"""""""""""""""""""""""""""""""""""""""""""""""""""""""
	)";
	usleep(2000000);

	cout << algernonAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""""""""""""""""|
| Alright, fine. You have a deal. Now, help me get my      |
| deliciousssssss applesssssssss. We will not sssstop until|
| you have helped me gather 10 applesssss.                 |
 """"""""""""""""""""""""""""""""""""""""""""""""""""""""""
	
	
	
	)";
	usleep(3000000);

	if(startGame() == 1)
	{
		cout << "Algernon is very dissssssapointed.\n";
		if(isTimeUp())
		{
			cout << "\033[31mTime's up!!\n";
			cout << "You ran out of time while you were helping the snake.\n";
			cout << "Now the transport has arrived to take you to the dungeons.\033[0m\n";
			cout << gameOverAscii <<  '\n';
		}
		exit(0);
	}



	
	usleep(1000000);

	if(isTimeUp())
	{
		cout << "\033[31mTime's up!!\n";
		cout << "You ran out of time while you were helping the snake.\n";
		cout << "Now the transport has arrived to take you to the dungeons.\033[0m\n";
		cout << gameOverAscii <<  '\n';
	}
	else
	{
		cout << algernonAscii << R"(
|""""""""""""""""""""""""""""""""""""|
| Thank you, human. You were not as  |
| usssselessss as I had presssssumed.|
 """"""""""""""""""""""""""""""""""""
	)" << '\n';
		usleep(1000000);
		cout << "...\n";
		usleep(1000000);
		cout << "...\n";
		usleep(1000000);
		cout << "...\n";
		usleep(1000000);
		cout << "...\n";
		usleep(1000000);
		cout << "...\n";

		cout << "\033[32mWoah, you're doing great!!\n";
		cout << "Congrats! You've just completed your first task.\n\n";
		cout << "Your second task is waiting for you in the tavern...\033[0m\n";

		system("mv ../.TAVERN ../TAVERN");
	}
	
	return 0;
}