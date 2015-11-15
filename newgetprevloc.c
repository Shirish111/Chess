
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

/*This file contains two functions getpreviousloc() which fetches the location and checkifvalid which checks for *match and barrier of the locations and returns NULL if not valid else returns the previous location if valid
*/
#include "newchess.h"
int *getpreviousloc(chess *q, int *locinput, int chk) {// Now Finds the location of coin to be moved
	int *prloc, i;
	switch(locinput[0]) {
		case PAWN:
			prloc = pawnsearch(q, locinput);
			return prloc;
			break;
		case ROOK: case BISHOP: case QUEEN:
			prloc = search(q, locinput[0], q->state, NULL, NULL);
			return prloc;
			break;
		case KNIGHT:
			prloc = search(q, locinput[0], q->state, NULL, NULL);
			return prloc;
			break;
		case KING:
			prloc = search(q, locinput[0], q->state, NULL, NULL);
			return prloc;
	}
}
int *checkifvalid(chess *q, int *locinput, int *prloc, int chk) {/* Checks for match and barrier */
	int valid, i, counter = 0, counter1 = 0;
	char *str;
	switch(locinput[0]) {
		case PAWN://Done
			if(prloc[0] == CONF) {//
				mvprintw(27, 110, "Ambiguity!");
				mvprintw(29, 110, "Please enter the previous location");
				while(1) {
					printstate(stdscr, q);
					str = getuserinput(stdscr);
					prloc = getinputlocationpr(q, str, locinput);
					if(prloc != NULL) {
						break;
					}
					else {
						mvprintw(27, 110, "Please enter correct input\n");
					}
				}
			}
			else if(prloc[0] == NOTFOUND) {
				//Location not found
				return NULL;
			}
			return prloc;
			break;
		case ROOK: case BISHOP: case QUEEN://Using list datastructure Done
			if(prloc[0] == NOTFOUND) {
				//printf("Location not found");
				return NULL;
			}
			else {//prloc found
				valid = match(q, prloc, locinput);
				if(valid == 1) {//valid
					valid = barrier(q, prloc, locinput, chk);//Check if there is any coin in between
					if(valid == 0) {//0 indicates no barrier
						counter++;
						counter1 = 1;
					}
				}
				if(prloc[4] != NOTFOUND) {

					valid = match(q, &prloc[4], locinput);
					if(valid == 1) {//valid
						valid = barrier(q, &prloc[4], locinput, chk);
						if(valid == 0) {
							counter++;
							counter1 = 2;
						}
					}
				}
				if(counter == 0) {//Location found but not matched or there is a barrier
					return NULL;
				}
				if(counter == 2) {
					while(1) {
						mvprintw(27, 110, "Ambiguity!");
						mvprintw(29, 110, "Please enter the previous location");
						printstate(stdscr, q);
						str = getuserinput(stdscr);
						prloc = getinputlocationpr(q, str, locinput);
						if(prloc != NULL) {
							return prloc;
						}
					}
				}
				else if(counter == 1 && counter1 == 1) {//If only first is valid
					return prloc;
				}
				else {//Second is valid
					return &prloc[4];
				}		
			}
			break;
		case KNIGHT:
			prloc = search(q, locinput[0], q->state, NULL, NULL);
			if(prloc[0] == NOTFOUND) {
				//printf("Not found\n");
				return NULL;
			}
			else {
				valid = match(q, prloc, locinput);
				if(valid == 1) {//valid
					valid = barrier(q, prloc, locinput, chk);//Check if there is any coin in between
					if(valid == 0) {//0 indicates no barrier
						counter++;
						counter1 = 1;
					}
				}
				if(prloc[4] != NOTFOUND) {
					valid = match(q, &prloc[4], locinput);
					if(valid == 1) {//valid
						valid = barrier(q, &prloc[4], locinput, chk);
						if(valid == 0) {
							counter++;
							counter1 = 2;
						}
					}
				}
				if(counter == 0) {
					return NULL;
				}
				if(counter == 2) {
					while(1) {
						mvprintw(27, 110, "Ambiguity!");
						mvprintw(29, 110, "Please enter the previous location");
						printstate(stdscr, q);
						str = getuserinput(stdscr);
						prloc = getinputlocationpr(q, str, locinput);
						if(prloc != NULL) 
							return prloc;
					}
				}
				else if(counter == 1 && counter1 == 1) {
					return prloc;
				}
				else {
					return &prloc[4];
				}		
			}
			break;
		case KING:
			valid = match(q, prloc, locinput);
			if(valid == 1) {
				return prloc;
			}
			return NULL;
	}
}

