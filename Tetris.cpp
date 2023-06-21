// Tetris.cpp

#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

void gotoXY(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printMatriz(char matriz1[4][4]){

     for(unsigned int i = 0; i < 4; ++i){
          for(unsigned int j = 0; j < 4; ++j){
               cout << matriz1[i][j] << ' ';
          }
          cout << endl;
     }
}

void rotarMatrizDer(char matriz[4][4]) {
	// Temp array
	int r[4][4];
	// Turning columns in rows
	for (int i = 0; i < 4; i++)	{
		for (int j = 0; j < 4; j++)	{
			r[i][j] = matriz[3-j][i];
		}
	}
	// Filling the original array
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)	{
			matriz[i][j] = r[i][j];
		}
	}
}
void rotarMatrizIzq(char matriz[4][4]) {
	//Temp array
	int r[4][4];
	//Turning columns in rows
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)	{
			r[i][j] = matriz[j][3-i];
		}
	}
	//Filling the original array
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)	{
			matriz[i][j] = r[i][j];
		}
	}
}

int main(){
	system("cls");
	int i, j, y;
	char x;
	
	int tetrominos[7];	// List of all pieces
	for(i = 0; i < 7; ++i) tetrominos[i] = i+1;
	char tetr1[4][4] = {{0, 0, 1, 0},{0, 0, 1, 0},{0, 0, 1, 0},{0, 0, 1, 0}}; // I piece
	char tetr2[4][4] = {{0, 0, 0, 0},{0, 1, 1, 0},{0, 1, 1, 0},{0, 0, 0, 0}}; // Square piece
	char tetr3[4][4] = {{32, 32, 65, 32},{32, 32, 65, 32},{32, 32, 65, 65},{32, 32, 32, 32}}; // L piece
	char tetr4[4][4] = {{0, 1, 0, 0},{0, 1, 0, 0},{0, 1, 1, 0},{0, 0, 0, 0}}; // L switched piece
	char tetr5[4][4] = {{0, 0, 0, 0},{0, 1, 1, 0},{0, 0, 1, 1},{0, 0, 0, 0}}; // Z piece
	char tetr6[4][4] = {{0, 0, 0, 0},{0, 1, 1, 0},{1, 1, 0, 0},{0, 0, 1, 0}}; // Z switched piece
	char tetr7[4][4] = {{0, 0, 0, 0},{0, 0, 1, 0},{0, 1, 1, 1},{0, 0, 0, 0}}; // T piece

	do{
		gotoXY(0,4);
		x = getch();
		switch (x)
		{
		case 'a':
			system("cls");
			rotarMatrizIzq(tetr3);
			printMatriz(tetr3);
						
			break;
		case 'd':
			system("cls");
			rotarMatrizDer(tetr3);
			printMatriz(tetr3);
			
			break;
		
		default:
			break;
		}
	} while (!0);

	for(x = 0; x < 7; ++x){
		for(i = 0; i < 4; ++i){
			for(j = 0; j < 4; ++j){
				switch(x){
					case 0:
						cout << tetr1[i][j] << ' ';
					break;

					case 1:
						cout << tetr2[i][j] << ' ';
					break;

					case 2:
						cout << tetr3[i][j] << ' ';
					break;

					case 3:
						cout << tetr4[i][j] << ' ';
					break;

					case 4:
						cout << tetr5[i][j] << ' ';
					break;

					case 5:
						cout << tetr6[i][j] << ' ';
					break;

					case 6:
						cout << tetr7[i][j] << ' ';
					break;
				}

			}
			cout << endl;
		}
		cout << endl;
	}

	return 0;
}
