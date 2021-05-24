// Name: Stef Pollo
// Date: 19 May 2021
// Program Name: 
// Purpose:

#include <iostream>
#include <string>
#include <unistd.h>
//#include "CLI-RPG/general.h"
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

// hides a file or dir from the player
void hideFile(string fileName)
{
	string cmd { "mv "+fileName+" ."+fileName};
	system(cmd.c_str());

}

// shows a file or dir to the player
void showFile(string fileName)
{
	string cmd { "mv ."+fileName+" "+fileName};
  system(cmd.c_str());
}

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

	//give confirmation msg for selected choice

	//index of selected choice from the options[] array
	return choice-1;
}

string playerCellAscii { R"(
   _______________________
     ||   ||     ||   ||
     ||   ||, , ,||   ||
     ||  (||/|/(\\||/ ||
     ||  ||| _'_`|||  ||
     ||   || o o ||   ||
     ||  (||  - `||)  ||
     ||   ||  =  ||   ||
     ||   ||\___/||   ||
     ||___||) , (||___||
    /||---||-\_/-||---||\
   / ||--_||_____||_--|| \
  (_(||)--||-----||-(||)__)
)" };
string jailGuardAscii{R"(                              
                          \      __      /         __
                           \_____()_____/         /  )
                           '============`        /  /
                            #---\  /---#        /  /
                           (# @\| |/@  #)      /  /
                            \   (_)   /       /  /
                            |\ '---` /|      /  /
                    _______/ \\_____// \____/ o_|
                   /       \  /     \  /   / o_|
                  / |           o|        / o_| \
                 /  |  _____     |       / /   \ \
                /   |  |===|    o|      / /\    \ \
               |    |   \@/      |     / /  \    \ \
               |    |___________o|__/----)   \    \/
               |    '              ||  --)    \     |
               |___________________||  --)     \    /
                    |           o|   ''''   |   \__/
                    |            |          |
)"};


int main()
{
	cout << "\nYou wake up in a dim cell. Your head feels like someone's been stomping on it since yesterday.\n"
		<< "You drag yourself into a sitting position and look around.\n";

    usleep(2000000);  //microseconds
    
  	cout << "There is no one else here, despite the cell "
		<< "clearly having been made to hold multiple people.\nThis must be the county jail.\nYou think hard, " 
		<< "but you cannot recall much of what happened last night. Your last memory is of a huge man yelling in your face, "
		<< "and then swinging a barstool at your head.\n\nAn officer is standing guard outside the cell, and notices you're awake.\n";

  	usleep(2000000);

	cout << playerCellAscii << R"(
|"""""""""""""""""""""""""""|
| Hello, sir. Mind telling  |
|  me what I'm doing here?  |
 """""""""""""""""""""""""""
 )";

	usleep(2000000);

	cout << jailGuardAscii << R"(
                |"""""""""""""""""""""""""""""""""""""""""""""""|
                | Don't act innocent with me, boy.              |
                | You know why you're here. After that massive	|
                | fight you started, you're lucky you weren't 	|
                | sent to the dungeons. Only a misdemeanor and  |
                | a "disturbing the peace" charge were" is too  |
                | light a sentence for you.                     |
                 """""""""""""""""""""""""""""""""""""""""""""""
)";
	usleep(3000000);

	cout << playerCellAscii << R"(
|"""""""""""""""""""""""""""""""|
| What fight? I hardly remember | 
| anything from last night.     |
 """""""""""""""""""""""""""""""
)";
	usleep(2000000);

	cout << jailGuardAscii << R"(
                |""""""""""""""""""""""""""""""""""""""""""""""""|
                | Well, well, well, isn't that convenient?       |
                | Alothough, you did take a pretty hard hit to 	 |
                | the head. You might actually be telling the    |
                | truth. Tell you what, I have an offer to make  |
                | to you, on behalf of the town.                 |
                 """"""""""""""""""""""""""""""""""""""""""""""""
)";
	usleep(2000000);

	cout << playerCellAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""""|
| Ohh? Sounds interesting. You know, I am a    |
| mercenary, whenever I'm not getting the carp |
| beat out of me in bar fights, hehe.          |
 """"""""""""""""""""""""""""""""""""""""""""""
)"; //carp isn't a typo
	usleep(3000000);

	cout << jailGuardAscii << R"(
                |""""""""""""""""""""""""""""""""""""""""""""""""""""""""""|
                | Great! The thing is, you aren't doing anyone any good    |
                | rotting behind those bars. So, the town of Nayney is     |
                | offering you the opportunity to atone for the massive bar| 
                | fight you started in a way other than just sitting here  |
                | in the dark.                                             |
                | You can complete five acts of community service for      |
                | the town, and afterwards, you will be freed without      |
                | consequence from any jail sentence.                      |
                 """"""""""""""""""""""""""""""""""""""""""""""""""""""""""
)";
	usleep(4000000);

	cout << playerCellAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""""|
| I see, and what happens if I say no?         |
 """"""""""""""""""""""""""""""""""""""""""""""
)";
	usleep(500000);

	cout << jailGuardAscii << R"(
                |"""""""""""""""""""""""""""""""""""""""""""""""""""""|
                | You will be sent to the dungeons in the capital,    |
                | where you will be serving your sentence of 10 years.|
                | Ohh and I almost forgot to mention, the entourage   |
                | coming to transport you to the dungeons will be here|
                | in about 20 minutes. So if you do agree to the tasks|
                | ,you will have to complete them before they arrive. |
                | Otherwise, you'll be sent to the dungeons no matter |
                | what.                                               |
                 """""""""""""""""""""""""""""""""""""""""""""""""""""
)";
  usleep(4000000);

	cout << "You must make a decision.\n";

  string options[]{"Yes","No"};
	int choice = makeDecision("Will you agree to complete the tasks?",options,2);
  cout << options[choice];

  if(choice == 0)
  {
    showFile("TOWN_SQUARE");
    system("mv TOWN_SQUARE/.FOREST TOWN_SQUARE/FOREST");

    cout << jailGuardAscii << R"(
                |""""""""""""""""""""""""""""""""""""""""""""""""""""""""""|
                | So then, you've decided to attempt the tasks. I've gotta |
                | warn you, it won't be easy. You have 20 minutes to       |
                | complete all 3 before the armed transport comes to       | 
                | collect you.                                             |
                | You may go into the town now. Look around for tasks you  |
                | may complete. More places will become available to you   |
                | the further you progress. Hurry up, and good luck!       |
                 """"""""""""""""""""""""""""""""""""""""""""""""""""""""""
      )";
      usleep(2000000);

    // start timer 20 min
    system("./.countdown.sh ");

  }
  else
  {
    	cout << jailGuardAscii << R"(
                |"""""""""""""""""""""""""""""""""""""""""""""""""""""""|
                | Well, I have to say I'm dissapointed, but I         |
                | shouldn't be surprised, I guess. You are a violent    |
                | drunk and a sword-for-hire, afterall. You can wait    |
                | here with me then, until your transport arrives in 20 |
                | minutes.                                              |
                 """""""""""""""""""""""""""""""""""""""""""""""""""""""
      )";

      usleep(2000000);

      cout << jailGuardAscii << R"(
                |"""""""""""""""""""""""""""""""""""""""""""""""""""""""|
                | How 'bout this, I'll go take my lunch break and come  |
                | back later to see if you've reconsidered the offer.   |
                | Judging by your head wound, you might not even        |
                | remember this conversation later. Hopefully, by then  |
                | you'll be thinking more clearly and recognize this    |
                | deal you've been offered.                             |
                 """""""""""""""""""""""""""""""""""""""""""""""""""""""   )" << '\n';
  }


	return 0;
}