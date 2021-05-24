#ifndef GENERAL_H // guard
#define GENERAL_H

#include <iostream>
using namespace std;

int getValidInt();

// hides a file or dir from the player
void hideFile(string fileName);


// shows a file or dir to the player
void showFile(string fileName);

int makeDecision(string prompt, string options[], int numOfOptions);


#endif