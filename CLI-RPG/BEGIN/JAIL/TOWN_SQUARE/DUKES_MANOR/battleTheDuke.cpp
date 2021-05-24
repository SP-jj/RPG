// Name: Stef Pollo
// Date: 19 May 2021
// Program Name: battleTheDuke.cpp
// Purpose: Play tic tac toe game against duke to win the game

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fstream>

using namespace std;

string gameOverAscii = R"(
░██████╗░░█████╗░███╗░░░███╗███████╗  ░█████╗░██╗░░░██╗███████╗██████╗░
██╔════╝░██╔══██╗████╗░████║██╔════╝  ██╔══██╗██║░░░██║██╔════╝██╔══██╗
██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░██║╚██╗░██╔╝█████╗░░██████╔╝
██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗
╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ╚█████╔╝░░╚██╔╝░░███████╗██║░░██║
░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝
		)";
string congratulationsAscii = R"(
░█████╗░░█████╗░███╗░░██╗░██████╗░██████╗░░█████╗░████████╗██╗░░░██╗██╗░░░░░░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
██╔══██╗██╔══██╗████╗░██║██╔════╝░██╔══██╗██╔══██╗╚══██╔══╝██║░░░██║██║░░░░░██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
██║░░╚═╝██║░░██║██╔██╗██║██║░░██╗░██████╔╝███████║░░░██║░░░██║░░░██║██║░░░░░███████║░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
██║░░██╗██║░░██║██║╚████║██║░░╚██╗██╔══██╗██╔══██║░░░██║░░░██║░░░██║██║░░░░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
╚█████╔╝╚█████╔╝██║░╚███║╚██████╔╝██║░░██║██║░░██║░░░██║░░░╚██████╔╝███████╗██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
░╚════╝░░╚════╝░╚═╝░░╚══╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░░╚═════╝░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░                                                                                                              
		)";
string dukeAscii = R"(
                    .
                   / \
                  _\ /_
        .     .  (,'v`.)  .     .
        \)   ( )  ,' `.  ( )   (/
         \`. / `-'     `-' \ ,'/
          : '    _______    ' :
          |  _,-'  ,-.  `-._  |
          |,' ( )__`-'__( ) `.|
          (|,-,'-._   _.-`.-.|)
          /  /<( o)> <( o)>\  \
          :  :     | |     :  :
          |  |     ; :     |  |
          |  |    (.-.)    |  |
          |  |  ,' ___ `.  |  |
          ;  |)/ ,'---'. \(|  :
      _,-/   |/\(       )/\|   \-._
_..--'.-(    |   `-'''-'   |    )-.`--.._
         `.  ;`._________,':  ,'
        ,' `/               \'`.
             `------.------'      
                    '
)";

// check if countdown timer has reached 20 min
bool isTimeUp()
{
	string gameLogText;
	fstream gameLogFile;
	gameLogFile.open("../../../../gameLog", ios::in);
	if (!gameLogFile) {
		cout << "Error:No such file\n";
		return false;
	}
	else {
		// get first line from file
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


const int GRID_SIZE = 3;

class Game
{
    private:
        char grid[GRID_SIZE][GRID_SIZE];
    
    public:
        int turnsPlayed; // keeps track of how many turns have been played in a game
                            // important because this number cannot exceed 9
                            // 'cause there are only 9 spots to fill in the grid
        bool isGameOver;

        // handle event where player wins
        void playerWins()
        {
            cout << "\n------ GAME OVER ------\n";
            cout << "Congratulations!!! You have defeated the Duke.\n";
            isGameOver = true;
        }

        // handle event where computer wins
        void computerWins()
        {
            cout << "\n------ GAME OVER ------\n";
            cout << "You've failed to defeat the evil Duke\n";
            isGameOver = true;
        }

        // handles event where tie occurs
        void tie()
        {
            cout << "There are no more moves to make. The game is a tie.\n";
            computerWins();
        }

        // returns char of winning player, returns Z if noone won
        void checkForWins()
        {  
            const char* winningCombinations[8] =    // 2^GRID_SIZE = 8
            {
                "123", "456", "789",    // horizontal
                "147", "258", "369",    //vertical
                "159", "357"            // diagonal
            };


            // iterate through each possible winning combo
            for(int i = 0;i < 8;i++)
            {
                bool win = true;

                // to check if current char in combo's iteration is same as previous char
                char prevPos = '0';
                
                const char* winningMove = winningCombinations[i];

                // if the chars on the grid in the win combo's places arent all the same, this isnt a win
                for (int j = 0; j < GRID_SIZE; j++)
                {
                    int enteredNum = winningMove[j] - '0';
                    int gridIndex = enteredNum - 1;

                    int row = gridIndex / GRID_SIZE;
                    int col = gridIndex % GRID_SIZE;

                    char gridChar = grid[row][col];

                    
                    if(prevPos == '0')
                    // if this is the check of the first space in the combo, it cant be a lose already.
                    {
                        prevPos = gridChar;
                    }
                    else if( prevPos == gridChar)
                    {
                        continue;
                    }
                    else
                    // if prevPos != gridChar, the letters dont match and this isnt a win
                    {
                        win = false;
                        break;
                    }
                }

                
                
                if (win)
                {
                    cout << "\n------ GAME OVER ------\n";
                    isGameOver = true;
                      // player has won
                    if(prevPos == 'X')
                    {
                        cout << "Congratulations!!! You have defeated the Duke.\n";
                    }
                    else
                    {
                        cout << "You've failed to defeat the evil Duke\n";
                        if(isTimeUp())
                        {
                            cout << "\033[31mYour time is up. The transport is here and you've failed to complete your missions.\033[0m\n";
                            cout << gameOverAscii;
                        }
                            
                        exit(0);
                    }
                    break;
                }

                // there have been a total of 9 turns and nobody has won yet
                // there are no more spaces to fill on the grid, so it's a tie
                if(turnsPlayed == 9)
                {
                    cout << "\n------ GAME OVER ------\n";
                    cout << "There are no more moves to make. The game is a tie.\n";
                    isGameOver = true;

                    if(isTimeUp())
                    {
                        cout << "\033[31mYour time is up. The transport is here and you've failed to complete your missions.\033[0m\n";
                        cout << gameOverAscii;
                    }
                    exit(0);
                }
            }
        }

        void generateGrid()
        {
            int positionValue = 1;
            for (int i = 0; i < GRID_SIZE; i++)
            {
                for (int j = 0; j < GRID_SIZE; j++)
                {
                    grid[i][j] = to_string(positionValue).c_str()[0];
                    positionValue++;
                }
                
            }

        }

        void askTurn()
        {
            int input;
            while(true)
            {
                cout << "Select the free position you'd like to fill: ";
                cin >> input;
                if(cin.fail() || input <1 || input >9 )
                {
                    cout << "You have to enter one of the numbers from the available positions.\n";
                    cin.clear();
                    cin.ignore(10000,'\n');
                }
                else
                {
                    int index = input - 1;

                    // / operator determines what row you're in
                    int row = index / GRID_SIZE;
                    // % operator determines what column you're in
                    int col = index % GRID_SIZE;

                    char gridPosition = grid[row][col];
                    if(gridPosition == 'X' || gridPosition == 'O')
                    {
                        cout << "That position is already taken. Choose another one.\n";
                    }
                    else
                    {
                        cout << "Your play:\t" << gridPosition << '\n';
                        grid[row][col] = 'X';
                        turnsPlayed++;
                        break;
                    }

                    
                }
            
            }
        }

        // int minimax(int depth,bool isMaximizing)
        // {
        //     int result = checkForWins(false);
        //     if(isMaximizing)
        //     {
        //     }
        //     return 0;
        // }

        // void AIBestMove()
        // {
        //     int bestScore = -9999;  // minimax score of best outcome
        //     int bestMove[2]{};      //grid coordinates of best move
        //     for (int x = 0; x < GRID_SIZE; x++)
        //     {
        //         for (int y = 0; y < GRID_SIZE; y++)
        //         {
        //             // is spot available
        //             if(grid[x][y] != 'X' && grid[x][y] !='O')
        //             {
        //                 char currentPos = grid[x][y];
        //                 grid[x][y] = 'O';       // temporarily change grid to test move's outcome
        //                 int score {minimax(0,false)};
        //                 grid[x][y] = currentPos;
        //                 if(score > bestScore)
        //                 {
        //                     bestScore = score;
        //                     bestMove[0] = x;
        //                     bestMove[1] = y;
        //                 }
        //             }
        //         }
        //     }         
        // }

        void computerPlayerTurn()
        {
            int compChoice{};
            while(true)
            {

                compChoice = ( rand() % 9) + 1;
            
                int row = (compChoice -1) / GRID_SIZE;
                int col = (compChoice -1)% GRID_SIZE;

                char positionVal = grid[row][col];
                
                //if random selected spot is taken, try another number
                if (positionVal == 'X' || positionVal == 'O')
                    continue;
                else
                {
                    grid[row][col] = 'O';
                    turnsPlayed++;
                    break;
                }

            }
            cout << "Duke's play:  \t" << compChoice << '\n';
        
        }

        void showGrid()
        {
            cout << "\n-------------\n";
            for (int i = 0; i < GRID_SIZE; i++)
            {
                cout << '|';
                for (int j = 0; j < GRID_SIZE; j++)
                {
                    cout << ' ' << grid[i][j] << " |";
                }
                cout << "\n-------------\n";
            }
        }

        Game()
        {
            turnsPlayed = 0;
            isGameOver = false;
            generateGrid();

            showGrid();
            checkForWins();

            while (! isGameOver )            
            {
                askTurn();
                checkForWins();

                if(isGameOver)
                    continue;

                computerPlayerTurn();
                showGrid();
                checkForWins();
            }
        }
};

int main()
{
    srand(time(nullptr));


    cout << dukeAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""|
| What is this!? Who are you and what are    |
| you doing in my home?                      |
| Guards? Guards! Arrest this tresspasser!   |
 """"""""""""""""""""""""""""""""""""""""""""  
    )" << '\n';
    usleep(2000000);

    cout << dukeAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""|
| Oh, I see. You think you can beat me. Well,|
| I'll warn you, you aren't the first fool to|
| try to beat me.                            |
 """"""""""""""""""""""""""""""""""""""""""""  
    )" << '\n';

    usleep(2000000);

    cout << dukeAscii << R"(
|""""""""""""""""""""""""""""""""""""""""""""|
| Alright, lets get this over with.          |
| If this ends up makeing me late for lunch, |
| I'll make you regret you ever stepped foot |
| in this town!!                             |
 """"""""""""""""""""""""""""""""""""""""""""  
    )" << '\n';
    

    Game game;


	if(isTimeUp())
	{
		cout << "\033[31mTime's up!!\n";
		cout << "You ran out of time while you were battling the Duke\033[0m\n";
		cout << gameOverAscii <<  '\n';
	}
	else
	{
        cout << "\033[32mWOOHOOO!! You've won the game!!\033[0m";
		cout  << congratulationsAscii << '\n';
		
	}
        
    return 0;
}