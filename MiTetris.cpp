// Tetris.cpp

#include<iostream>
#include<iomanip>
#include<conio.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
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

void rotarMDer(char matriz[4][4], char arena[20][10], int leng, int x, int y) {
	int r[leng][leng];	// Temp array
	int k = y -5;	// Convert x to arena index
	int l = x - 11;	// Convert y to arena index
	int i = 0, j = 0;	// For index 
	// Turning columns in rows
	for (i = 0; i < leng; i++)	{
		for (j = 0; j < leng; j++)	{
			r[i][j] = matriz[leng-1-j][i];
		}
	}
	// Validate laterals:
	bool possible = true;
	for(i = 0; i < leng; ++i){
		for(j = 0; j < leng; ++j){
			if(-37 == r[i][j]){		// Try to draw rotated piece
				// If it can not, possible = false
				if(l + j < 0 || l + j > 9){
					possible = false;
					i = leng;
					break;
				}
				if(k + i > 19){	// Validate bottom
					possible = false;
					i = leng;
					break;
				}
				if(-37 == arena[k + i][l + j]){	// Validate other pieces
					possible = false;
					i = leng;
					break;
				}
			}
		}
	}
	// Filling the original array if possible == true
	if(possible){
		for (i = 0; i < leng; i++) {
			for (j = 0; j < leng; j++)	{
				matriz[i][j] = r[i][j];
			}
		}
	}
}
void rotarMIzq(char matriz[4][4], char arena[20][10], int leng, int x, int y) {
	int r[leng][leng];	// Temp array

	int k = y -5;	// Convert x to arena index
	int l = x - 11;	// Convert y to arena index
	int i = 0, j = 0;	// For index 

	//Turning columns in rows
	for (i = 0; i < leng; i++) {
		for (j = 0; j < leng; j++){
			r[i][j] = matriz[j][leng-1-i];
		}
	}
	// Validate if it can rotate by bounds
	bool possible = true;
	for(i = 0; i < leng; ++i){
		for(j = 0; j < leng; ++j){
			if(-37 == r[i][j]){		// Try to draw rotated piece
				// If it can not, possible = false
				if(l + j < 0 || l + j > 9){	// Validate borders
					possible = false;
					i = leng;
					break;
				}
				if(k + i > 19){ // Validate bottom
					possible = false;
					i = leng;
					break;
				}
				if(-37 == arena[k + i][l + j]){	// Validate other pieces
					possible = false;
					i = leng;
					break;
				}
			}
		}
	}
	// Filling the original array if possible == true
	if(possible){
		for (i = 0; i < leng; i++) {
			for (j = 0; j < leng; j++){
				matriz[i][j] = r[i][j];
			}
		}
	}
}

void printM(char matriz1[4][4], int leng, int x, int y){	// Original array, length and x y bounds
    for(int i = 0; i < leng; ++i){
         for(int j = 0; j < leng; ++j){
			gotoXY(x + j, y + i);
			if(-37 == matriz1[i][j]) cout << matriz1[i][j];
         }
    }
}

void clearM(char matriz1[4][4], int leng, int x, int y){
	for(int i = 0; i < leng; ++i){
		for(int j = 0; j < leng; ++j){
			gotoXY(x + j, y + i);
			if(-37 == matriz1[i][j]) cout << char(32);
		}
	}
}

void moveMLeft(char matriz1[4][4], char arena[20][10], int leng, int &x, int y){	// x argumento por referencia
	// Convert x, y to arena index
	int k = y - 5, l = x - 11;
	int last = 0;
	bool line = 0;
	bool possible = true;
	for(int i = 0; i < leng; ++i){
		line = false;
		for(int j = leng-1; j >= 0; --j){
			if(-37 == matriz1[i][j]){
				// Find the far left and save l + j (x)
				last = l + j;
				line = true;
			}
		}
		if(line){	// If line == true
			if(0 == last){
				possible = false;
			} else if(-37 == arena[k + i][last - 1]){
				possible = false;
			}
		}
	}
	if(possible){
		clearM(matriz1, leng, x, y);
		--x;
		printM(matriz1, leng, x , y);
	}
}
void moveMRight(char matriz1[4][4], char arena[20][10], int leng, int &x, int y){	// x reference parameter
	// Convert x, y to arena index
	int k = y - 5, l = x - 11;
	int last = 0;
	bool line = 0;
	bool possible = true;
	for(int i = 0; i < leng; ++i){
		line = false;
		for(int j = 0; j < leng; ++j){
			if(-37 == matriz1[i][j]){
				// Find the far right and save l + j (x)
				last = l + j;
				line = true;
			}
		}
		if(line){	// If line == true
			if(9 == last){
				possible = false;
			} else if(-37 == arena[k + i][last + 1]){
				possible = false;
			}
		}
	}
	if(possible){	// Move it if possible == true
		clearM(matriz1, leng, x, y);
		++x;
		printM(matriz1, leng, x , y);
	}
}

bool moveMDown(char matriz1[4][4], char arena[20][10], int leng, int x, int &y){	// x reference parameter
	// Convert x, y to arena index
	int k = y - 5, l = x - 11;
	int last=0;
	bool line = 0;
	bool possible = true;
	for(int i = 0; i < leng; ++i){
		line = false;
		for(int j = 0; j < leng; ++j){
			// Find the lower end and save j + k (y)
			if(-37 == matriz1[j][i]){
				 last = j + k;
				 line = true;
			}
		}
		if(line){ // If line == true
			if(19 == last){
				return possible = false;
			} else if(-37 == arena[last + 1][l + i]) {
				return possible = false;
			}
		}
	}
	if(possible){	// Move it if possible == true
		clearM(matriz1, leng, x, y);
		++y;
		printM(matriz1, leng, x , y);
	}
	return possible;
}

void drawArena(){
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

	gotoXY(26, 6);
	cout << "SCORE";
	gotoXY(26, 12);
	cout << "LEVEL";
	gotoXY(26, 15);
	cout << "LINES";
	gotoXY(24, 16);

}

void drawScoreStatus(int score, int level, int lines){
	gotoXY(24, 7);
	cout << setw(7) << right << score;
	gotoXY(24, 13);
	cout << setw(7) << right << level;
	gotoXY(24, 16);
	cout << setw(7) << right << lines;
}

void selectRandom(int &list){
	srand(time(0));
	list = 1 + rand()%7;
}

void clearArena(char arena[20][10]){
	int i=0, j=0;
	for(i = 0; i < 20; ++i){
		for(j = 0; j < 10; ++j){
			arena[i][j] = 32;
			gotoXY(11 + j, 5 + i);
			cout << ' ';
		}
	}
}

void gameOverArena(char arena[20][10]){
	int i=0, j=0;
	for(i = 0; i < 20; ++i){
		for(j = 0; j < 10; ++j){
			gotoXY(11 + j, 5 + i);
			cout << '.';
		}
	}
	gotoXY(14, 9); cout << "GAME";
	gotoXY(14, 11);	cout << "OVER";
	gotoXY(13, 14); cout << "PRESS";
	gotoXY(15, 16);	cout << "R";
	gotoXY(15, 18);	cout << "TO";
	gotoXY(12, 20);	cout << "RESTART";
}

void setPiece(char matriz[4][4], char arena[20][10], int leng, int &x, int &y){
	int k = y - 5, l = x - 11;
	int i = 0, j = 0;
	printM(matriz, leng, x, y);
	for(i = leng-1; i >= 0; --i){
		for(j = 0; j < leng; ++j){
			if(-37 == matriz[i][j]){
				arena[i + k][j + l] = -37;
			}			
		}
	}
	x = 14, y = 5;
	gotoXY(x, y);
}

void scanArena(char arena[20][10], int y, int &score, int &lines){
	int i=0, plus=0;
	int k = 0, l = 0;
	bool complete;

	for(k = y - 5; k < 20; ++k){
		complete = true;
		for(l = 0; l < 10; ++l){
			if(32 == arena[k][l]){
				complete = false;
			}
		}
		if(complete){
			++plus;
			while(l > 0){
				arena[k][--l] = 32;
				gotoXY(l + 11, k + 5);
				cout << ' ';
			} 
			for(i = k-1; i >= 0; --i){
				for(l = 0; l < 10; ++l){
					arena[i+1][l] = arena[i][l];
					gotoXY(l + 11, i + 6);
					cout << arena[i][l];
				}

			}
		}
	}
	lines += plus;
	switch(plus){
		case 1:	score += 200;
		break;
		case 2:	score += 500;
		break;
		case 3:	score += 1500;
		break;
		case 4:	score += 6000;
		break;
	}
}

void startPause(){
	int i=0 , j=0;
	for(i = 0; i < 20; ++i){
		for(j = 0; j < 10; ++j){
			gotoXY(11 + j, 5 + i);
			cout << ' ';
		}
	}
	gotoXY(14, 6); cout << "HIT";
	gotoXY(13, 8); cout << "START";
	gotoXY(14, 10); cout << "TO";
	gotoXY(12, 12); cout << "CONTINUE";
	gotoXY(14, 14); cout << "GAME";
}
void endPause(char arena[20][10]){
	int i=0 , j=0;
	for(i = 0; i < 20; ++i){
		for(j = 0; j < 10; ++j){
			gotoXY(11 + j, 5 + i);
			cout << arena[i][j];
		}
	}
}

bool gameOver(char arena[20][10], char matriz[4][4]){
	int i=0 , j=0;
	for(i = 0; i < 4; ++i){
		for(j = 0; j < 4; ++j){
			if(-37 == matriz[i][j] &&
			   -37 == arena[i][j + 3]){
				return true;	
			}
		}
	}
	return false;
}
void drawCover(){
	gotoXY(0,5);
	cout << "_|_|_| _|_|_|_|_|_| _|_|   _|_|_| _|_|\n"
    		"  _|   _|      _|   _|  _|   _|  _|\n"
    	    "  _|   _|_|    _|   _|_|     _|   |_|\n"
    	    "  _|   _|      _|   _|  _|   _|     _|\n"
    		"  _|   _|_|_|  _|   _|  _| _|_|_| _|_|\n";
	cout << "\n"
			"	A:   Move left\n"
			"	Q:   Rotate left\n"
			"	D:   Move right\n"
			"	E:   Rotate right\n"
			"	P:   Pause\n"
			"	ESC: Exit\n";;
	cout << "\nPress any key to start and ESC to exit";
                                                               

}

int main(){

	bool down = 0;
	int i=0, j=0, x=0, y=0, list=0, q=0, score = 0, lines = 0, level=0;
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
	for(i = 0; i < 20; ++i){	// Filling arena with spaces
		for(j = 0; j < 10; ++j){
			arena[i][j] = 32;
		}
	}


	// Console shape:
	system("mode con: cols=38 lines=30");
	system("title Tetris");
	system("color 0B");
	system("cls");

	hideCursor();
	drawCover();
	q = getch();
	if(27 == q){
		exit(1);
	}
	system("cls");
	drawArena();
	drawScoreStatus(score, level, lines);
	x = 14, y = 5;			// x, y initial bounds to start printing
	j = x - 11, i = y - 5;	// i, j inital bounds to the arena array

	// Print random piece:
	selectRandom(list);
	
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
	}

	do{
		for(q = 0; q < 24; ++q){
		Sleep(20 - level * 2);

		if(kbhit()){
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
							//clearM(tetr2, 4, x, y);
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
							rotarMIzq(tetr1, arena, 4, x, y);
							printM(tetr1, 4, x, y);
						break;
						case 2:
							//printM(tetr2, 4, x, y);
						break;
						case 3:
							rotarMIzq(tetr3, arena, 3, x, y);
							printM(tetr3, 3, x, y);
						break;
						case 4:
							rotarMIzq(tetr4, arena, 3, x, y);
							printM(tetr4, 3, x, y);
						break;
						case 5:
							rotarMIzq(tetr5, arena, 3, x, y);
							printM(tetr5, 3, x, y);
						break;
						case 6:
							rotarMIzq(tetr6, arena, 3, x, y);
							printM(tetr6, 3, x, y);
						break;
						case 7:
							rotarMIzq(tetr7, arena, 3, x, y);
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
							//clearM(tetr2, 4, x, y);
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
							rotarMDer(tetr1, arena, 4, x, y);
							printM(tetr1, 4, x, y);
						break;
						case 2:
							//printM(tetr2, 4, x, y);
						break;
						case 3:
							rotarMDer(tetr3, arena, 3, x, y);
							printM(tetr3, 3, x, y);
						break;
						case 4:
							rotarMDer(tetr4, arena, 3, x, y);
							printM(tetr4, 3, x, y);
						break;
						case 5:
							rotarMDer(tetr5, arena, 3, x, y);
							printM(tetr5, 3, x, y);
						break;
						case 6:
							rotarMDer(tetr6, arena, 3, x, y);
							printM(tetr6, 3, x, y);
						break;
						case 7:
							rotarMDer(tetr7, arena, 3, x, y);
							printM(tetr7, 3, x, y);
						break;
						default:				
						break;
					}
				break;

				case 'S':
				case 's':
					++score;
					// Finish the cycle to go down immediatly
					q = 24;
				break;

				case 27:
					// Finish the cycle to exit
					q = 24;
				break;
				case 'P':
				case 'p':
					// Pause
					q=0;
					startPause();
					gotoXY(14, 6); cout << "HIT";
					gotoXY(13, 8); cout << "START";
					gotoXY(14, 10); cout << "TO";
					gotoXY(12, 12); cout << "CONTINUE";
					gotoXY(14, 14); cout << "GAME";
					do{	// Infinit cycle until P key pressed again
						q = getch();
						if(27 == q){
							in = 27;
							q = 'P';
						}
					} while (q != 'P' && q != 'p');
					endPause(arena);
					break;
				}	
			}
		}
		switch(list){
			case 1:
				down = moveMDown(tetr1, arena, 4, x, y);
			break;
			case 2:
				down = moveMDown(tetr2, arena, 4, x, y);
			break;
			case 3:
				down = moveMDown(tetr3, arena, 3, x, y);
			break;
			case 4:
				down = moveMDown(tetr4, arena, 3, x, y);
			break;
			case 5:
				down = moveMDown(tetr5, arena, 3, x, y);
			break;
			case 6:
				down = moveMDown(tetr6, arena, 3, x, y);
			break;
			case 7:
				down = moveMDown(tetr7, arena, 3, x, y);	
			break;
		}
		if(!down){	// If it can not go down more
			switch(list){
				case 1:
					setPiece(tetr1, arena, 4, x, y);
				break;
				case 2:
					setPiece(tetr2, arena, 4, x, y);
				break;
				case 3:
					setPiece(tetr3, arena, 3, x, y);
				break;
				case 4:
					setPiece(tetr4, arena, 3, x, y);
				break;
				case 5:
					setPiece(tetr5, arena, 3, x, y);
				break;
				case 6:
					setPiece(tetr6, arena, 3, x, y);
				break;
				case 7:
					setPiece(tetr7, arena, 3, x, y);
				break;
			}
			scanArena(arena, y, score, lines);
			level = lines / 10;
			drawScoreStatus(score, level, lines);

			// Print random piece:
			selectRandom(list);

			switch(list){
				case 1:
					printM(tetr1, 4, x, y);
					down = gameOver(arena, tetr1);
				break;
				case 2:
					printM(tetr2, 4, x, y);
					down = gameOver(arena, tetr2);
				break;
				case 3:
					printM(tetr3, 3, x, y);
					down = gameOver(arena, tetr3);
				break;
				case 4:
					printM(tetr4, 3, x, y);
					down = gameOver(arena, tetr4);
				break;
				case 5:
					printM(tetr5, 3, x, y);
					down = gameOver(arena, tetr5);
				break;
				case 6:
					printM(tetr6, 3, x, y);
					down = gameOver(arena, tetr6);
				break;
				case 7:
					printM(tetr7, 3, x, y);
					down = gameOver(arena, tetr7);
				break;
			}
			
			if(down){	// If down(gameOver) == true
		
				gameOverArena(arena);
				do{
					in = getch();
					if(in == 27) break;
				}while(in != 'R' && in != 'r');

				if(in == 'R' || in == 'r'){
					for(i = 2; i <= 3 ; ++i){
						for(j = 0; j < 34; ++j){
							gotoXY(j, i);
							cout << ' ';
						}
					}
					clearArena(arena);
					score = level = lines = 0;
					drawScoreStatus(score, level, lines);
					x = 14, y = 5;			// x, y initial bounds to start printing
					j = x - 11, i = y - 5;	// i, j inital bounds to the arena array

					// Print random piece:
					selectRandom(list);
					
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
					}
				}
			}
		}
	} while (in != 27);
					
	return 0;
}
