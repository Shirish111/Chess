
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

/*This function deals with the player vs player mode of the game
 */
#include "newchess.h"
int p_vs_p_mode(WINDOW *win) {
	wclear(win);
	char *str;
	int undoredo1 = 0, valid, i, resigncounter = 0, in;
	int *prloc, *locinput;
	chess a;
	init(&a);
	display(win, &a);
	while(1) {
	  
		pawnpromotion(&a);
		valid = verifycheck(&a);/* Verify check for the present state */
		if(valid == CHECK) {
			valid = checkmate(&a);/* Verify checkmate for the present state */
			if(valid == CHECKMATE) {
				mvprintw(23, 110, "CHECKMATE!!!");
				getch();
				writetofile(&a, "checkmate");
				if(declarewinner(&a)) {/* If checkmate declare the winner */
					writetofile(&a, "Done");
					break;
				}
				else {
					writetofile(&a, "back");
				}
				continue;
			}
			else {/* Convey check */
				mvwprintw(win, 18, 110, "CHECK To ");
				writetofile(&a, "Check");
				if(a.state == WHITE) {
					mvwprintw(win, 18, 119, "WHITE\n");
				}
				else {
					mvwprintw(win, 18, 119, "BLACK\n");
				}
			}
		}

		else {
			a.enable = DISABLE;
			/* Verify for stalemate*/
			valid = draw(&a, STALEMATE);
			if(valid == DRAW) {
				if(declaredraw(&a, "STALEMATE")) {
					break;
				}
			}
		}
		a.enable = DISABLE;
		/* Verify for threefold repetition */
		valid = draw(&a, THREEFOLD_REPETITION);
		if(valid == DRAW) {
			if(declaredraw(&a, "THREEFOLD_REPETITION")) {
				break;
			}
		}
		/* Will verify for 50 step rule */
		valid = draw(&a, FIFTY_STEPS_RULE);
		if(valid == DRAW) { 
			if(declaredraw(&a, "FIFTY_STEPS_RULE")) {
				break;
			}
		} 
		/* Verify for Insufficient material */
		valid = draw(&a, INSUFFICIENT_MATERIAL);
		if(valid == DRAW) {
			if(declaredraw(&a, "INSUFFICIENT_MATERIAL")) {
				break;
			}
		}
		a.enable = ENABLE;
		while(1) {
			printstate(stdscr, &a);/* Convey who is supposed to play(WHITE or BLACK) */
			str = getuserinput(stdscr);
			if(str == NULL) { 
				mvprintw(18, 112, "INVALID INPUT");
				continue;
			}
			else if(strcmp(str, "enable") == 0) {
				enable(&a, str);
				continue;
			}
			else if(strcmp(str, "npass") == 0) {
				if(npassant(&a, 0)) {/* Npassant */
					writetofile(&a, str);
					break;
				}
				else {
					mvwprintw(stdscr, 28, 112, "Npassant not possible");
					getch();
					continue;
				}
			}
			else if(strcmp(str, "0-0") == 0 || strcmp(str, "0-0-0") == 0) {
				if(castling(&a, str)) {
					writetofile(&a, str);
					break;
				}
				else {
					mvwprintw(stdscr, 20, 110, "Castling is not possible");
					continue;
				}
			}
			else if(strcmp(str, "resign") == 0) {
				if(resign(&a)) {
					resigncounter = 1;
					break;
				}
				else {
					continue;
				}
			}
			else if(strcmp(str, "help") == 0 || strcmp(str, "about") == 0) {
				display_help_about(stdscr, str);
				display(stdscr, &a);
				continue;
			}
			else if(strcmp(str, "save") == 0) {
				savefile(&a);
				continue;
			}
			else if(strcmp(str, "quit") == 0 || strcmp(str, "exit") == 0) {
				mvprintw(20, 110, "Are you sure you want to quit?");
				mvprintw(22, 117, "1. Yes\t2. No");
				mvscanw(24, 123, "%d", &in);
				if(in == 1) {
					resigncounter = 1;
					break;
				}
				else {
					display(stdscr, &a);
					continue;
				}
			}
			else if(strcmp(str, "open") == 0) {
				openmoves(&a);
				continue;
			}
			else if(strcmp(str, "draw") == 0) {
				if(offerdraw(&a)) {
					resigncounter = 1;
					break;
				}
				else {
					continue;
				}
			}
			else if(strcmp(str, "moves") == 0) {
				readfromfile(&a);
				continue;
			}
			else if((strcmp(str, "undo") == 0) || (strcmp(str, "redo") == 0)) {
				writetofile(&a, str);
				undoredo(&a, str);
				undoredo1 = 1;
				break;
			}
			else if(strlen(str) > 4) {
				mvwprintw(stdscr, 18, 112, "Invalid input");
				continue;
			}
			locinput =  getinputlocation(&a, str);/* Converts the string into int array */
			if(locinput == NULL) {
				mvwprintw(stdscr, 18, 112, "Invalid Input");
				continue;
			}
			prloc = getpreviousloc(&a, locinput, NOCHECK);
			prloc = checkifvalid(&a, locinput, prloc, NOCHECK);
			if(prloc == NULL) {
				mvwprintw(stdscr, 18, 112, "Invalid Input");
				continue;
			}
			push(&a, &a.s, prloc, locinput);
			move1(&a, prloc, locinput, str);
			valid = verifycheck(&a);
			if(valid == CHECK) {
				a.c.count = 0;
				mvprintw(22, 110, "Illegal Move");
				mvprintw(24, 110, "You got a CHECK!");
				changestate(&a);
				undoredo(&a, "undo");
				doupdate();
				continue;
			}
			if(strcmp(str, "moveslist") != 0) {
				writetofile(&a, str);
			}
			break;
		}
		if(resigncounter == 1) {
			break;
		}
		if(undoredo1 == 1) {
			undoredo1 = 0;
			display(win, &a);
			continue;
		}
		display(win, &a);
		changestate(&a);
	}
	for(i = 0; i < 8; i++) {
		free(a.p[i]);
	}
	return QUITW;
}
