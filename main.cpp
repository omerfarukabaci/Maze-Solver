#include "stack.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

using namespace std;

// maze
char lab[15][22] = {
"#o###################",
"#     #      #    # #",
"# ### # ###### ## # #",
"# # #        # #  # #",
"# # ### ######## ## #",
"#     # # ##   #    #",
"### # # # ## # # ####",
"# # # # #    #      #",
"# # # # # ######### #",
"# # # # # #       # #",
"# # #   # # #####   #",
"# # ##### # #   #####",
"#         #   #     #",
"###################E#" };

void printlab(char l[15][22]) {
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 21; j++)
			cout << l[i][j];
		cout << endl;
	}
	cout << endl << endl;
}
int main(){
	Stack s;
	s.create();
	int gi, gj, ci, cj;

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 21; j++){
			if (lab[i][j] == 'o'){ gi = i; gj = j; }
			if (lab[i][j] == 'E'){ ci = i; cj = j; }
		} // end nested for
	} // end for

	position entrance = { gj, gi, 0, 0, 0, 0, 0 };
	position exit = { cj, ci, 0, 0, 0, 0, 0 };
	position p = entrance;
	position decision;

	p.camefrom = LEFT;
	printlab(lab);
	bool goback = false;

	while (p.x != exit.x || p.y != exit.y) {
		system("cls");
		lab[p.y][p.x] = 'o';
		printlab(lab);

		//first find in how many directions we can move
		if (!goback) { //if not calculated before
			p.right = 0; p.left = 0; p.down = 0; p.up = 0;
			if (p.x < 20 && lab[p.y][p.x + 1] != '#' && lab[p.y][p.x + 1] != 'o') p.right = 1; //right
			if (p.x > 0 && lab[p.y][p.x - 1] != '#' && lab[p.y][p.x - 1] != 'o') p.left = 1; //left
			if (p.y < 14 && lab[p.y + 1][p.x] != '#' && lab[p.y + 1][p.x] != 'o') p.down = 1; //down
			if (p.y > 0 && lab[p.y - 1][p.x] != '#' && lab[p.y - 1][p.x] != 'o') p.up = 1; //up
		} // end if

		else goback = false;

		//here, one of the possible moves is selected
		bool moved = true;
		position past = p;
		if (p.left && p.camefrom != LEFT){
			p.x--; p.camefrom = RIGHT; past.left = 0;
		}else if (p.right && p.camefrom != RIGHT){
			p.x++; p.camefrom = LEFT; past.right = 0;
		}else if (p.down && p.camefrom != DOWN){
			p.y++; p.camefrom = UP; past.down = 0;
		}else if (p.up && p.camefrom != UP){
			p.y--; p.camefrom = DOWN; past.up = 0;
		}else moved = false; //one direction (the minimum) is open, but this is the direction we came from
		
		if (p.x != exit.x || p.y != exit.y) {
			if ((p.down + p.up + p.right + p.left) > 1) {
				//there is more than one choice, push onto stack and //continue in that chosen direction. Let the choices //you have not selected remain marked on the stack.
				s.push(past);
			} // end nested if
			if (!moved) { // has to go back
				if (!s.isempty()) {
					decision = s.pop();
					while (p.x != decision.x || p.y != decision.y){
						system("cls");
						lab[p.y][p.x] = ' ';

						if (lab[p.y][p.x + 1] == 'o') p.x++;
						else if (lab[p.y][p.x - 1] == 'o') p.x--;
						else if (lab[p.y + 1][p.x] == 'o') p.y++;
						else if (lab[p.y - 1][p.x] == 'o') p.y--;

						printlab(lab);

						// to observe path
						std::this_thread::sleep_for(0.2s);
					} // end while
					p = decision;
					goback = true;
				} // end second nested if
			} // end first nested if
		} // end if
		// to observe path
		std::this_thread::sleep_for(0.2s);
	} // end of while

	lab[p.y][p.x] = 'o';
	printlab(lab);
	cout << "PATH found" << endl;
	system("pause");
	
	return 0;
}
