
/*****************************************************************************
 * Copyright (C) Shirishkumar Togarla shirishtogarla533@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/* This file contains declarewinner() function which is used to declare winner and also asks the user for resuming the game
 */
#include "newchess.h"
int declarewinner(chess *q) {
	int n; 
	if(q->state == WHITE) {
		clear();
		init_pair(13, COLOR_WHITE, COLOR_RED); 
		bkgd(COLOR_PAIR(13));
		mvprintw(LINES / 2 - 4, COLS /2 - 4, "BLACK WINS");
		mvprintw(LINES / 2 - 2, COLS /2 - 6, "Want to resume?");
		mvprintw(LINES / 2, COLS /2 - 5,"1. Yes 2. No");
		mvprintw(LINES / 2 + 2, COLS /2 - 5, "Enter choice");
		curs_set(1);
		mvscanw(LINES / 2 + 4, COLS /2, "%d", &n);
		curs_set(0);
		refresh();
		display(stdscr, q);
		if(n == 1) {
			undoredo(q, "undo");
			undoredo(q, "undo");
			display(stdscr, q);
			return 0;
		}
		else {
			savefile(q);
			getch();
			return 1;
		}
	}
	else {
		clear();
		init_pair(13, COLOR_WHITE, COLOR_RED); 
		bkgd(COLOR_PAIR(13));
		mvprintw(LINES / 2 - 4, COLS /2 - 4, "WHITE WINS");
		mvprintw(LINES / 2 - 2, COLS /2 - 6, "Want to resume?");
		mvprintw(LINES / 2, COLS /2 - 5,"1. Yes 2. No");
		mvprintw(LINES / 2 + 2, COLS /2 - 5, "Enter choice");
		/* mvprintw(22, 110, "Want to resume?"); */
		/* mvprintw(24, 110, "1. Yes 2. No"); */
		/* mvprintw(26, 110, "Enter choice"); */
		/* mvwaddch(win, 26, 123, ':'); */
		curs_set(1);
		mvscanw(LINES / 2 + 4, COLS / 2, "%d", &n);
		curs_set(0);
		refresh();
		display(stdscr, q);
		if(n == 1) {
			undoredo(q, "undo");
			undoredo(q, "undo");
			display(stdscr, q);
			return 0;
		}
		else {
			savefile(q);
			getch();
			return 1;
		}
	}
}
