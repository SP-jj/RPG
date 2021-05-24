// // Name: Stef Pollo
// // Date: 19 May 2021
// // Program Name: 
// // Purpose:

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>

#ifndef SNAKE_H
#define SNAKE_H

using namespace std;

struct snakePart
{
	int x,y;
	snakePart(int col, int row);
	snakePart();
};

class snakeClass
{

	public:

		snakeClass();
		~snakeClass();
		void start();

	private:	
		int points, delay, applesGathered, maxWidth, maxHeight;
		char direction, snakePartChar, foodChar;
		char borderChar;
		bool gotFood;

		snakePart food;
		vector<snakePart> snake;

		void spawnFood();
		bool collision();
		void moveSnake();

	public:
		snakeClass();
		~snakeClass();
		int start();


};

#endif