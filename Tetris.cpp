// Tetris.cpp

#include<iostream>
#include<windows.h>
using namespace std;

void gotoXY(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(){

	int i, j, x, y;
	
	int tetrominos[7];	// List of all pieces
	for(i = 0; i < 7; ++i) tetrominos[i] = i+1;



	do{


	} while (!0);

	return 0;
}
