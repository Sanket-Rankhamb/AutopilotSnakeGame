#include <iostream>
#include "GameBoard.h"
#include <conio.h>
#include "Macros.h"
#include <Windows.h>
using namespace std; 

void welcome();
void header();
void status( int score, int x, int y, int gameLoopStatus );
int gameLoop();

#define GAME_OVER 3
const int SleepTime = 100;

int main() {
	
	welcome();
	while(1){ 
		int score = gameLoop();
		cout << "Your score is "<< score << endl; 
		cout << "Press Enter Key to Restart , Press 'O' key to Exit";
		char c = getch();
		system("cls");
		if( c == 'o' || c == 'O' ) break;
	}
	return 0;
}

int gameLoop(){
	
	header();
	GameBoard gameBoard(MIN_X, MIN_Y, MAX_X, MAX_Y);
	gameBoard.drawBorder();
	gameBoard.drawSnake();
	gameBoard.generateFood();
	gameBoard.drawFood();

	Snake& snake = gameBoard.getSnake();
	int direction = snake.getDirection(); // initial direction
	int pause = true;
	int score = 0;
	status( score, snake.getHeadX() - MIN_X , snake.getHeadY() - MIN_Y, pause );
		
	while(1){
		
		if(kbhit()){
			char c = getch();
			bool wasPaused = pause;
			pause = false;
			switch(c){
				
				case 'd':
				case 'D':
					if( direction != LEFT ) direction = RIGHT;
					else pause = true;
					break;
					
				case 'a': 
				case 'A':
					if( direction != RIGHT ) direction = LEFT; 
					else pause = true;
					break;
					
				case 'w':
				case 'W':
					if( direction != DOWN ) direction = UP; 
					else pause = true;
					break;
					
				case 's': 
				case 'S':
					if( direction != UP ) direction = DOWN; 
					else pause = true;
					break;
				case 'o':
				case 'O':exit(0);
				default: pause = wasPaused;
			}
		}
		
		
		if( !pause ){
		
			switch(direction){
				case RIGHT: snake.moveRight(); break;
				case LEFT: snake.moveLeft(); break;
				case UP: snake.moveUp(); break;
				case DOWN: snake.moveDown(); break;
				default: break;
			}
			
			gameBoard.drawSnake();
			
			if( gameBoard.isBorderCollision() || snake.isSelfCollision() ){
				cout << (char) 7;
				status( score, snake.getHeadX() - MIN_X, snake.getHeadY() - MIN_Y, GAME_OVER);
				// set cursor position below the rectangele
				HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
				COORD pos = { 0, MAX_Y + 2};
				SetConsoleCursorPosition( console, pos );
				Sleep(2000);
				break;
			} 
			
			if(gameBoard.isSnakeEatingFood()){
				score++;
				snake.grow();
				gameBoard.generateFood();
				gameBoard.drawFood();
			}
			
			Sleep(SleepTime); // for slowing the speed of processing
	    }
	    
	    status( score, snake.getHeadX() - MIN_X, snake.getHeadY() - MIN_Y, pause );
	    
	    if( pause ) while( !kbhit() );
	}
	
	return score;
}

void welcome(){
	system("cls");
	cout << "********************** WELCOME TO snake GAME ***********************" << endl;
	cout << endl << "#Controls {" << endl << endl;
	cout << "   RIGHT : D" << endl;
	cout << "   LEFT  : A" << endl;
	cout << "   UP    : W"  << endl;
	cout << "   DOWN  : S" << endl;
	cout << "   PAUSE : Opposite Direction" << endl;
	cout << "   RESUME: Non Opposite Direction" << endl;
	cout << "}" << endl;
	cout << endl << "Press any key to start game..";
	getch();
	system("cls");
}

void header(){
	cout << "                         SNAKE GAME "<< endl << endl;
	cout << "RIGHT:D  LEFT:A  UP:W  DOWN:S  PAUSE:OppositeDirection  RESUME:NonOppositeDirection  " ;
	cout << "Exit:O" << endl << endl;
}

void status( int score, int x, int y, int gameLoopStatus ){
	HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD pos = { STATUS_LINE_X, STATUS_LINE_Y };
	SetConsoleCursorPosition(console, pos);
	for( int i = 1; i <= 40; ++i ) cout << " ";
	SetConsoleCursorPosition(console, pos);
	cout << "SCORE:" << score << " X:" << x << " Y:" << y << " ";
	if( gameLoopStatus == 0) cout << "GameLoop:Running";
	else if( gameLoopStatus == 1) cout << "GameLoop:Paused";
	else cout << "GameLoop:GameOver";
}
