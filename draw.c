
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

/*This file contains the draw funtion which is used to verify if a draw has taken place
 */
#include "newchess.h"
int draw(chess *q, int n) {
	int i, j, *prloc;
	stacknode *p, **loc;
	char c;
	int counter1 = 0, counter2 = 0;
	switch(n) {
		case STALEMATE:
			/* 1. Stalemate	 */
			/* 	You can do this checking if moves can be made by big pieces first and then check if it can be made by pawns */
			if(pawnsmove(q)) {
				return 1; 
			} 
			if(piecesmove(q)) {
				return 1;
			}

			return DRAW;
			break;
		case THREEFOLD_REPETITION:
			/* 	1. Search for pawns and find if the next locations are empty or can be killed and are legal */
			/* 	2. Search for big pieces and make moves */
			/* 2. Threefold Repetition  */
			if(q->s.count >= 6) {
				loc = (stacknode **) malloc(sizeof(stacknode *) * 6);
				p = q->s.tail;
				for(i = 0; i < 6; i++) {
					loc[i] = p;
					p = p->previous;
				}
				for(i = 0; i < 4; i++) {
					if(loc[0]->prloc[i] != loc[2]->locinput[i] || loc[0]->locinput[i] != loc[2]->prloc[i] || loc[2]->prloc[i] != loc[4]->locinput[i] || loc[2]->locinput[i] != loc[4]->prloc[i] || loc[1]->prloc[i] != loc[3]->locinput[i] || loc[1]->locinput[i] != loc[3]->prloc[i] || loc[3]->prloc[i] != loc[5]->locinput[i] || loc[3]->locinput[i] != loc[5]->prloc[i]) {
						// free(loc);
						return 1;
					}
				}
				free(loc);
				return DRAW;
			}
			return 1;
			break;
		case INSUFFICIENT_MATERIAL:
			/* You can do this by undo and redo functions and then comparing if the moves are same */
			/* 3. Insufficient coins to make a checkmate  */
			/* 1. check if no pawns are alive. 2. If yes then check for the big pieces */
			for(i = 0; i < 8; i++) {
				for(j = 0; j < 8; j++) {
					if(q->p[i][j].name[1] != 'K' && q->p[i][j].status == ALIVE) {
						if(q->p[i][j].name[1] == 'N' || q->p[i][j].name[1] == 'B') {
							if(q->p[i][j].name[0] == 'W') {
								counter1++;
							}
							else {
								counter2++;
							}
							if(counter1 > 1 || counter2 > 1) {
								return 1;
							}
						}
						else {
							return 1;
						}
					}
				}
			}
			return DRAW;
			break;
			/* 4. Offer draw */
			/* You can do this by just putting the code in the p_vs_p_mode  */
		case FIFTY_STEPS_RULE:
			/* 5. 50 steps rule */

			if(q->state == WHITE) {
				c = 'B';
			}
			else {
				c = 'W';
			}
			for(i = 0; i < 8; i++) {
				for(j = 0; j < 8; j++) {
					if(q->p[i][j].name[0] == c && q->p[i][j].name[1] != 'K') {
						return 1;
					}
				}
			}
			/* No other coins left so start counting */
			static int countsteps = 0;
			countsteps++;
			mvprintw(30, 110, "Steps = %d", countsteps);
			getch();
			if(countsteps != 50) {
				return 1;
			}
			return DRAW;
			/* Now count steps */
			/* This can be done by checking the list and pawns */
	}
	//display(stdscr, q);
}
