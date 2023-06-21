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
	char	// All tetrominós are char arrays
	tetr1[4][4] = {{32, 32, -36, 32},{32, 32, -36, 32},{32, 32, -36, 32},{32, 32, -36, 32}}, // I piece
	tetr2[4][4] = {{32, 32, 32, 32},{32, -36, -36, 32},{32, -36, -36, 32},{32, 32, 32, 32}}, // Square piece
	tetr3[4][4] = {{32, 32, -36, 32},{32, 32, -36, 32},{32, 32, -36, -36},{32, 32, 32, 32}}, // L piece
	tetr4[4][4] = {{32, -36, 32, 32},{32, -36, 32, 32},{32, -36, -36, 32},{32, 32, 32, 32}}, // L switched piece
	tetr5[4][4] = {{32, 32, 32, 32},{32, -36, -36, 32},{32, 32, -36, -36},{32, 32, 32, 32}}, // Z piece
	tetr6[4][4] = {{32, 32, 32, 32},{32, -36, -36, 32},{-36, -36, 32, 32},{32, 32, -36, 32}}, // Z switched piece
	tetr7[4][4] = {{32, 32, 32, 32},{32, 32, -36, 32},{32, -36, -36, -36},{32, 32, 32, 32}}; // T piece

	do{
		gotoXY(32,4);
		x = getch();
		switch (x) {
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
	} while (!kbhit() && 0);

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
	system("pause");
	return 0;
}
