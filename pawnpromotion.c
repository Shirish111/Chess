
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

/*This file contains the function pawnpromotion()
 *It deals with the pawn promotion rule in chess
 */
#include "newchess.h"
void pawnpromotion(chess *q) {
	int i, j, counter = 0, *newpiece, n, *prloc;
	int state = q->prevstate;
	static int ch = 0;
	newpiece = (int *)malloc(sizeof(int) * 4);
	if(ch != 0) {
		state = q->state;
	}
	if(state == WHITE) {
		i = 0;
	}
	else {
		i = 7;
	}
	for(j = 0; j < 8; j++) {
		if(q->p[i][j].name[1] == 'P' && q->p[i][j].color == state) {
			counter = 1;
			break;
		}
	}
	if(counter == 1) {
		n = 0;
		for(newpiece[0] = KNIGHT; newpiece[0] < KING; newpiece[0]++) {
			prloc = search(q, newpiece[0], state, NULL, NULL);
			if(prloc[0] != NOTFOUND && prloc[4] != NOTFOUND) {
				n++;
			}
		}
		newpiece[1] = i;
		newpiece[2] = j;
	}
	/* You can't have more than two pieces of the same kind */
	if(n == 4) {
		ch = 1;
		mvprintw(33, 110, "You can't have more than");
		mvprintw(34, 110, "two pieces of a kind!");
		return;
	}
	/* Pawnpromotion */
	if(counter == 1) {
		ch = 0;
		newpiece[3] = NOKILL;
		do {
			mvprintw(26, 110, "Pawn Promotion!");
			mvprintw(28, 110, "Select one of the choices");
			mvprintw(30, 97, "1. QUEEN    2. ROOK   3. BISHOP    4. KNIGHT");
			mvscanw(32, 110, "%d", &n);
			switch(n) {
				case 1:
					newpiece[0] = QUEEN;
					break;
				case 2:
					newpiece[0] = ROOK;
					break;
				case 3:
					newpiece[0] = BISHOP;
					break;
				case 4:
					newpiece[0] = KNIGHT;
					break;
				default:
					n = -1;
					break;
			}
			if(n != -1) {
				prloc = search(q, newpiece[0], state, NULL, NULL);
				if(prloc[0] != NOTFOUND && prloc[4] != NOTFOUND) {
					mvprintw(33, 110, "You can't have more than");
					mvprintw(34, 110, "two pieces of a kind!"); 
					n = -1;
				}
			}
		}
		while(n == -1);
		q->p[i][j].name[0] = concolor(state);
		q->p[i][j].name[1] = rconvertp(newpiece[0]);
		q->p[i][j].status = ALIVE;
		q->p[i][j].color = state;
		append(q, newpiece, state);
		q->s.tail->locinput[0] = newpiece[0];
		display(stdscr, q);
		free(newpiece);
	}
}


