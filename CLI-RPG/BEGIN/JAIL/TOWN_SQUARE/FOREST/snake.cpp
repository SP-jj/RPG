// Name: Stef Pollo
// Date: 19 May 2021
// Program Name: 
// Purpose:

#include "snake.h"

snakePart::snakePart(int col, int row)
{
	x = col;
	y = row;
}
snakePart::snakePart()
{
	x = 0;
	y = 0;
}

snakeClass::snakeClass()
{
	// scr == screen,	stdscr = standard screen

	initscr();				//starts ncurses mode

	// getch() is how user will input direction of snake
	// this is so that getch() doesnt wait for user to press a key
	nodelay(stdscr,true);	

	keypad(stdscr,true);	// so we can use/recognize keypresses

	noecho();				// so not everything gets logged to console
	curs_set(0);
	getmaxyx(stdscr,maxHeight,maxWidth);

	srand(time(nullptr));

	// print max height and max width at top right
	// move(1, maxWidth-20);
	// printw("Screen dimensions");
	// move(2, maxWidth-15);
	// printw("%d",maxWidth);
	// move(2, maxWidth-7);
	// printw("%d",maxHeight);
	


	//initialize some vars
	snakePartChar = 'X';  // what the body of the snake will look like on the console(ex.  XXXXXXX )
	borderChar = (char)219;  // ascii code for rectangle
	foodChar = '*';

	food.x = 0;
	food.y = 0;

	// starting snake length is 5
	for (int i = 0; i < 5; i++)
	{
		// spawns snake at center of screen in a horizontal line
		snake.push_back( snakePart(20+i,15) );	// adds five snakePart elements to the vector
	}
	points = 0;
	applesGathered = 0;
	delay = 110000;		//microseconds
	gotFood = false;
	direction = 'l';
	spawnFood();

	// create top border of snake's field in console
	for (int i = 0; i < maxWidth-1; i++)
	{
		move(0,i);
		addch(borderChar);
	}
	// bottom border
	for (int i = 0; i < maxWidth-1; i++)
	{
		move(maxHeight-2, i);
		addch(borderChar);
	}
	// left border
	for (int i = 0; i < maxHeight-1; i++)
	{
		move(i,0);
		addch(borderChar);
	}
	// right border
	for (int i = 0; i < maxHeight-1; i++)
	{
		move(i, maxWidth-2);
		addch(borderChar);
	}

	// display amount of points earned in bottom left corner
	move(maxHeight-1,0);
	printw("POINTS: %d", points);
	move(maxHeight-1,15);
	printw("APPLES GATHERED: %d",applesGathered);

	//draw snake
	for (int i = 0; i < snake.size(); i++)
	{
		move(snake[i].y,snake[i].x);		
		addch('X');
	}
	
	// draw first food on screen
	move(food.y,food.x);
	addch(foodChar);
	
	refresh();
}

snakeClass::~snakeClass()
{
	nodelay(stdscr,false);
	endwin();
}

void snakeClass::spawnFood()
{
	while(true)
	{
		//generate random coordinates to spawn food in
		int tmpx = rand()%maxWidth+1;
		int tmpy = rand()%maxHeight+1;

		// if the random coordinates are on the snake, they arent valid, 
		// and a new iteration begins, with new random coordinates
		bool valid = true;
		for (int i = 0; i < snake.size(); i++)
		{
			if(snake[i].x == tmpx && snake[i].y == tmpy)
			{
				valid = false;
				break;
			}
		}
		if (!valid)
			continue;

		// if random coordinates are on or outside of the borders,
		// they arent valid
		if(tmpx >= maxWidth-2 || tmpy >= maxHeight-3)
			continue;

		// set random coordinates as location of food
		food.x = tmpx;
		food.y = tmpy;	
		break;
		
	}
	
	// draw food on screen
	move(food.y,food.x);
	addch(foodChar);

	refresh();
}

bool snakeClass::collision()
{
	//if snake head collides with:
	//   left border			right border
	if(snake[0].x == 0 || snake[0].x == maxWidth-1 
	//	top border				bottom border
	|| snake[0].y == 0 || snake[0].y == maxHeight-2)
	{
		return true;
	}
		
	
	// if snake collides with itself
	for( int i=2; i<snake.size(); i++)
	// loop starts at 2 because head cannot collide with itself[0],
	// or the snakePart right next to it[1]
	{
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return true;
	}

	// if snake collides with food
	if(snake[0].x == food.x && snake[0].y == food.y)
	{
		gotFood = true;
		
		//create new food( there is only 1 food obj at anytime on the screen)
		spawnFood();

		// each food obj is worth 10 pts
		points += 10;
		applesGathered++;

		// draw updated points
		move(maxHeight-1,0);
		printw("POINTS: %d", points);
		move(maxHeight-1,15);
		printw("APPLES GATHERED: %d",applesGathered);

		// everytime points reaches a multiple of 100(ex. 100,200,300...)
		// the difficulty increases by increasing the speed of the snake
		if(points%100 == 0)
			delay -= 10000;
	}

	return false;
}

void snakeClass::moveSnake()
{
	// get usr input
	int tmp = getch();

	// if ((tmp >= int('A') && tmp <= int('Z')) || (tmp >= int('a') && tmp <= int('z')))
	// 	tmp
	switch (tmp)
	{
		case KEY_LEFT:
		
			if( direction != 'r')
			direction = 'l';
			break;
		
		case KEY_RIGHT:
			if( direction != 'l')
			direction = 'r';
			break;
		
		case KEY_DOWN:
			if( direction != 'd')
			direction = 'u';
			break;
		
		case KEY_UP:
			if( direction != 'u')
			direction = 'd';
			break;
		// user wants to quit game
		case KEY_BACKSPACE:
			direction = 'q';
		default:
			break;
	}

	// if snake didnt get food, (meaning they didnt grow)
	// the last snakePart gets deleted( a new head will be 
	// added immediately after, so the snake isnt getting shortened)
	if( ! gotFood )
	{
		move( snake[snake.size()-1].y , snake[snake.size()-1].x);
		addch(' ');
		refresh();
		// remove last element from vector array
		snake.pop_back();
	}
	else
	{
		// reset gotFood value to false
		gotFood = false;
	}

	// add head in correct direction:
	// left means x decreases by 1 & y doesnt change
	if(direction == 'l')
		snake.insert( snake.begin(), snakePart(snake[0].x-1, snake[0].y));
	// right means x increases by 1 & y doesnt change
	else if(direction == 'r')
		snake.insert( snake.begin(), snakePart(snake[0].x+1, snake[0].y));
	// up means x doesnt change & y increases by 1
	else if(direction == 'u')
		snake.insert( snake.begin(), snakePart(snake[0].x, snake[0].y+1));
	// right means x doesnt change & y decreases by 1
	else if(direction == 'd')
		snake.insert( snake.begin(), snakePart(snake[0].x, snake[0].y-1));
	
	// draw new head
	move(snake[0].y,snake[0].x);
	addch(snakePartChar);

	refresh();
}

int snakeClass::start()
{
	while(applesGathered<10)
	{
		// if snake collides with something(other than food)
		// game stops, msg 'game over' is printed
		if( collision() )
		{
			move(maxHeight/2,maxWidth/2-4);
			printw("GAME OVER");
			move(maxHeight/2+1,maxWidth/2-15);
			printw("You failed to help Algernon");
			refresh();
			usleep(3000000);
			return 1;
		}
		moveSnake();

		//player quits
		if(direction == 'q')
			return 1;

		//stop time between each iteration(screen update)
		usleep(delay);
	}

	move(maxHeight/2-1,maxWidth/2-4);
	printw("GAME WON");
	move(maxHeight/2+1,maxWidth/2-15);
	printw("Press any key to continue...");
	refresh();
	getch();
	return 0;

	
}