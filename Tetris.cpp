// Tetris.cpp

#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

void hideCursor(){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void gotoXY(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void rotarMDer(char matriz[4][4], int x) {
	// Temp array
	int r[x][x];
	// Turning columns in rows
	for (int i = 0; i < x; i++)	{
		for (int j = 0; j < x; j++)	{
			r[i][j] = matriz[x-1-j][i];
		}
	}
	// Filling the original array
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++)	{
			matriz[i][j] = r[i][j];
		}
	}
}
void rotarMIzq(char matriz[4][4], int x) {
	// Parameters: original array and length
	//Temp array
	int r[x][x];
	//Turning columns in rows
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++)	{
			r[i][j] = matriz[j][x-1-i];
		}
	}
	//Filling the original array
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++)	{
			matriz[i][j] = r[i][j];
		}
	}
}

void printM(char matriz1[4][4], int leng, int x, int y){	// Original array, length and x y bounds
    for(int i = 0; i < leng; ++i){
         for(int j = 0; j < leng; ++j){
			gotoXY(x + j, y + i);
			if(-37 == matriz1[i][j]) cout << matriz1[i][j];
         }
         cout << endl;
    }
}

void clearM(char matriz1[4][4], int leng, int x, int y){
	for(int i = 0; i < leng; ++i){
		for(int j = 0; j < leng; ++j){
			gotoXY(x +j, y + i);
			if(-37 == matriz1[i][j]) cout << char(32);

		}
	}
}

void moveMLeft(char matriz1[4][4], char arena[20][10], int leng, int &x, int y){	// x argumento por referencia
	// Convert x, y to arena index
	int k = y - 5, l = x - 11;
	bool possible = true;
	for(int i = 0; i < leng; ++i){
		for(int j = 0; j < leng; ++j){
			if(-37 == matriz1[j][i]){
				if(l + i == 0){
					possible = false;
					i = leng;
					break;
				}
			}
		}
	}
	if(true == possible){
		clearM(matriz1, leng, x, y);
		--x;
		printM(matriz1, leng, x , y);
	}
}
void moveMRight(char matriz1[4][4], char arena[20][10], int leng, int &x, int y){	// x argumento por referencia
	// Convert x, y to arena index
	int k = y - 5, l = x - 11;
	bool possible = true;
	for(int i = 0; i < leng; ++i){
		for(int j = 0; j < leng; ++j){
			if(-37 == matriz1[j][i]){
				if(l + i == 9){
					possible = false;
					i = leng;
					break;
				}
			}
		}
	}
	if(true == possible){
		clearM(matriz1, leng, x, y);
		++x;
		printM(matriz1, leng, x , y);
	}

}

void drawArena(){
	// Drawing indications:
	gotoXY(11, 27);
	cout << "Exit: Enter";
	gotoXY(11, 1);
	cout << "To move: A D";
	gotoXY(11, 2);
	cout << "Change piece: W";
	gotoXY(11, 3);
	cout << "Rotate it: Q E";
	// Drawing arena:
	int x=0, y=0;
	for(x = 10, y = 5; y < 25; ++y){
		gotoXY(x, y);
		cout << char(186);
		gotoXY(x+11, y);
		cout << char(186);
	}
	gotoXY(x, y);
	cout << char(200);
	while(x < 21){
		gotoXY(++x, y);
		cout << char(205);
	}
	gotoXY(x, y);
	cout << char(188);
}

int main(){
	system("mode con: cols=30 lines=30");
	system("title Tetris");
	system("cls");
	int i=0, j=0, x=0, y=0, list=0;
	char in=0;
	
	char	// All tetrominós are char arrays
	tetr1[4][4] = {{32, 32, -37, 32},{32, 32, -37, 32},{32, 32, -37, 32},{32, 32, -37, 32}}, // I piece
	tetr2[4][4] = {{32, 32, 32, 32},{32, -37, -37, 32},{32, -37, -37, 32},{32, 32, 32, 32}}, // Square piece
	tetr3[4][4] = {{32, -37, 32, 32},{32, -37, 32, 32},{32, -37, -37, 32},{32, 32, 32, 32}}, // L piece
	tetr4[4][4] = {{32, -37, 32, 32},{32, -37, 32, 32},{-37, -37, 32, 32},{32, 32, 32, 32}}, // L switched piece
	tetr5[4][4] = {{-37, -37, 32, 32},{32, -37, -37, 32},{32, 32, 32, 32},{32, 32, 32, 32}}, // Z piece
	tetr6[4][4] = {{32, -37, -37, 32},{-37, -37, 32, 32},{32, 32, 32, 32},{32, 32, 32, 32}}, // Z switched piece
	tetr7[4][4] = {{32, -37, 32, 32},{-37, -37, -37, 32},{32, 32, 32, 32},{32, 32, 32, 32}}; // T piece
	char arena[20][10];

	hideCursor();
	drawArena();


	
	x = 14, y = 5;			// x, y initial bounds to start printing
	j = x - 11, i = y - 5;	// i, j inital bounds to the arena array
	
	// Print random piece:
	printM(tetr7, 4, x, y);
	// Using list as a list 1-7
	list = 7;

	do{
		in = getch();
		switch (in) {
		case 'A':
		case 'a':
			switch(list){
				case 1:
					moveMLeft(tetr1, arena, 4, x, y);
				break;
				case 2:
					moveMLeft(tetr2, arena, 4, x, y);
				break;
				case 3:
					moveMLeft(tetr3, arena, 3, x, y);
				break;
				case 4:
					moveMLeft(tetr4, arena, 3, x, y);
				break;
				case 5:
					moveMLeft(tetr5, arena, 3, x, y);
				break;
				case 6:
					moveMLeft(tetr6, arena, 3, x, y);
				break;
				case 7:
					moveMLeft(tetr7, arena, 3, x, y);
							
				break;
				default:				
				break;
			}
			
			break;
		case 'D':
		case 'd':
			switch(list){
				case 1:
					moveMRight(tetr1, arena, 4, x, y);
				break;
				case 2:
					moveMRight(tetr2, arena, 4, x, y);
				break;
				case 3:
					moveMRight(tetr3, arena, 3, x, y);
				break;
				case 4:
					moveMRight(tetr4, arena, 3, x, y);
				break;
				case 5:
					moveMRight(tetr5, arena, 3, x, y);
				break;
				case 6:
					moveMRight(tetr6, arena, 3, x, y);
				break;
				case 7:
					moveMRight(tetr7, arena, 3, x, y);
							
				break;
				default:				
				break;
			}
			break;
		case 'q':
		case 'Q':
			// Clear last tetrominó
			switch(list){
				case 1:
					clearM(tetr1, 4, x, y);
				break;
				case 2:
					clearM(tetr2, 4, x, y);
				break;
				case 3:
					clearM(tetr3, 3, x, y);
				break;
				case 4:
					clearM(tetr4, 3, x, y);
				break;
				case 5:
					clearM(tetr5, 3, x, y);
				break;
				case 6:
					clearM(tetr6, 3, x, y);
				break;
				case 7:
					clearM(tetr7, 3, x, y);
				break;
				default:				
				break;
			}
			// Print turned tetrominó
			switch(list){
				case 1:
					rotarMIzq(tetr1, 4);
					printM(tetr1, 4, x, y);
				break;
				case 2:
					printM(tetr2, 4, x, y);
				break;
				case 3:
					rotarMIzq(tetr3, 3);
					printM(tetr3, 3, x, y);
				break;
				case 4:
					rotarMIzq(tetr4, 3);
					printM(tetr4, 3, x, y);
				break;
				case 5:
					rotarMIzq(tetr5, 3);
					printM(tetr5, 3, x, y);
				break;
				case 6:
					rotarMIzq(tetr6, 3);
					printM(tetr6, 3, x, y);
				break;
				case 7:
					rotarMIzq(tetr7, 3);
					printM(tetr7, 3, x, y);
				break;
				default:				
				break;
			}

		break;
		case 'e':
		case 'E':
			// Clear last tetrominó
			switch(list){
				case 1:
					clearM(tetr1, 4, x, y);
				break;
				case 2:
					clearM(tetr2, 4, x, y);
				break;
				case 3:
					clearM(tetr3, 3, x, y);
				break;
				case 4:
					clearM(tetr4, 3, x, y);
				break;
				case 5:
					clearM(tetr5, 3, x, y);
				break;
				case 6:
					clearM(tetr6, 3, x, y);
				break;
				case 7:
					clearM(tetr7, 3, x, y);
				break;
				default:				
				break;
			}
			// Print turned tetrominó
			switch(list){
				case 1:
					rotarMDer(tetr1, 4);
					printM(tetr1, 4, x, y);
				break;
				case 2:
					printM(tetr2, 4, x, y);
				break;
				case 3:
					rotarMDer(tetr3, 3);
					printM(tetr3, 3, x, y);
				break;
				case 4:
					rotarMDer(tetr4, 3);
					printM(tetr4, 3, x, y);
				break;
				case 5:
					rotarMDer(tetr5, 3);
					printM(tetr5, 3, x, y);
				break;
				case 6:
					rotarMDer(tetr6, 3);
					printM(tetr6, 3, x, y);
				break;
				case 7:
					rotarMDer(tetr7, 3);
					printM(tetr7, 3, x, y);
				break;
				default:				
				break;
			}
		break;

		case 'W':
		case 'w':
			// Clear last tetrominó
			switch(list){
				case 1:
					clearM(tetr1, 4, x, y);
				break;
				case 2:
					clearM(tetr2, 4, x, y);
				break;
				case 3:
					clearM(tetr3, 3, x, y);
				break;
				case 4:
					clearM(tetr4, 3, x, y);
				break;
				case 5:
					clearM(tetr5, 3, x, y);
				break;
				case 6:
					clearM(tetr6, 3, x, y);
				break;
				case 7:
					clearM(tetr7, 3, x, y);
				break;
				default:				
				break;
			}
			++list;
			if(list >= 8) list = 1;
			// Print turned tetrominó
			switch(list){
				case 1:
					printM(tetr1, 4, x, y);
				break;
				case 2:
					printM(tetr2, 4, x, y);
				break;
				case 3:
					printM(tetr3, 3, x, y);
				break;
				case 4:
					printM(tetr4, 3, x, y);
				break;
				case 5:
					printM(tetr5, 3, x, y);
				break;
				case 6:
					printM(tetr6, 3, x, y);
				break;
				case 7:
					printM(tetr7, 3, x, y);
				break;
				default:				
				break;
			}
		break;


		break;

		default:
		break;
		}
	} while (in != 13);
					
	return 0;
}
