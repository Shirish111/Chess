
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

/*This file includes some functions which do int* to string, int to char, char to int conversions and also a function which checks the correctness of the location
 */
#include "newchess.h"
int* getinputlocation(chess *q, char *str) {
	int i = 0;
	int *locinput;
	locinput = (int*)malloc(sizeof(int) * 4);
	locinput[3] = NOKILL;
	while(str[i] != '\0') {
		switch(str[i]) {
			case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
				locinput[1] = converti(str[i]);
				break;
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
				if(i == 0) {
					locinput[0] = PAWN;
				}
				locinput[2] = convertj(str[i]);
				break;
			case 'P':
				locinput[0] = PAWN;
				break;
			case 'R':
				locinput[0] = ROOK;
				break;
			case 'N':
				locinput[0] = KNIGHT;
				break;
			case 'B':
				locinput[0] = BISHOP;
				break;
			case 'Q':
				locinput[0] = QUEEN;
				break;
			case 'K':
				locinput[0] = KING;
				break;
			case 'x': case 'X':
				locinput[3] = KILL;
				break;
			default:
				mvprintw(18, 112, "Invalid input");
				return NULL;
		}
		i++;
	}
	locinput = correctness(q, locinput);
	return locinput;
}
int *correctness(chess *q, int *locinput) {
	if(locinput[3] == KILL) {
		if(q->p[locinput[1]][locinput[2]].status != ALIVE || q->p[locinput[1]][locinput[2]].color != q->prevstate) {
			if(q->enable == ENABLE) {
				mvprintw(20, 110, "(Killing your own piece)");	
			}
			return NULL;
		}
	}
	else {
		if(q->p[locinput[1]][locinput[2]].status == ALIVE) {
			if(q->enable == ENABLE) {
				mvprintw(20, 110, "(Status of the location is ALIVE)");
			}
			return NULL;
		}
	}
	return locinput;
}
int convertj(char c) {
	return(c - 'a');
}
int converti(char c) {
	return('8' - c);
}
int convertp(char c) {
	switch(c) {
		case 'P':
			return PAWN;
		case 'R':
			return ROOK;
		case 'N':
			return KNIGHT;
		case 'B':
			return BISHOP;
		case 'Q':
			return QUEEN;
		case 'K':
			return KING;
		case '_':
			return NOTHING;
	}
}
char rconvertp(int c) {
	switch(c) {
		case PAWN:
			return 'P';
		case ROOK:
			return 'R';
		case KNIGHT:
			return 'N';
		case BISHOP:
			return 'B';
		case QUEEN:
			return 'Q';
		case KING:
			return 'K';
	}
}
int* getinputlocationpr(chess *q, char *str, int *loc) {
	int i = 0;
	int *locinput;
	locinput = (int*)malloc(sizeof(int) * 4);
	locinput[3] = NOKILL;
	while(str[i] != '\0') {
		switch(str[i]) {
			case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
				locinput[1] = converti(str[i]);
				break;
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
				if(i == 0) {
					locinput[0] = PAWN;
				}
				locinput[2] = convertj(str[i]);
				break;
			case 'P':
				locinput[0] = PAWN;
				break;
			case 'R':
				locinput[0] = ROOK;
				break;
			case 'N':
				locinput[0] = KNIGHT;
				break;
			case 'B':
				locinput[0] = BISHOP;
				break;
			case 'Q':
				locinput[0] = QUEEN;
				break;
			case 'K':
				locinput[0] = KING;
				break;
			case 'x': case 'X':
				locinput[3] = KILL;
				break;
			default:
				mvprintw(25, 110, "Invalid input");
				return NULL;
		}
		i++;
	}
	/* Now check for its correctness */
	if(loc[0] != PAWN && loc[0] == locinput[0]) {
		i = match(q, locinput, loc);
		if(i == 1) {//valid
			i = barrier(q, locinput, loc, 0);
			if(i == 0) {
				return locinput;
			}
		}
		return NULL;
	}
	else if(loc[0] == PAWN && loc[0] == locinput[0]) {
		if((q->state == WHITE && loc[1] - locinput[1] == -1 || q->state == BLACK && loc[1] - locinput[1] == 1) && (loc[2] - locinput[2] == -1 || loc[2] - locinput[2] == 1)) {
			return locinput;
		}
		return NULL;
	}
	return NULL;
}
char concolor(int state) {
	if(state == WHITE) {
		return 'W';
	}
	else if(state == BLACK) {
		return 'B';
	}
	else {
		return '_';
	}
}
