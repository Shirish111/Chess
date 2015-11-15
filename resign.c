/*This file includes the function resign() which asks for the user if he wants to resign
 */
#include "newchess.h"
int resign(chess *q) {
	int n;
	clear();
	init_pair(13, COLOR_WHITE, COLOR_RED); 
	bkgd(COLOR_PAIR(13));
	do {
		mvprintw(LINES / 3, COLS / 2 - 14, "Do you really want to resign?");
		mvprintw(LINES / 3 + 2, COLS / 2 - 5, "1. Yes  2. No");
		mvprintw(LINES / 3 + 4, COLS /2 - 5, "Enter choice");
		mvscanw(LINES / 3 + 6, COLS / 2, "%d", &n);
		if(n == 1) {
			q->enable = DISABLE;
			if(q->state == WHITE) {
				mvprintw(LINES / 2 + 1, COLS /2 - 4, "BLACK WINS");
				getch();
				savefile(q);
			}
			else {
				mvprintw(LINES / 2 + 1, COLS /2 - 4, "WHITE WINS");
				getch();
				savefile(q);
			}
			refresh();
			getch();
			return 1;
		}
		else if(n == 2) {
			refresh();
			display(stdscr, q);
			return 0;
		}
		else {
			mvprintw(LINES / 4 + 6, COLS / 2 - 10, "Please enter correct choice\n");
			n = -1;
		}
	}
	while(n == -1);

}
