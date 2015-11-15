
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

/*This file contains function npassant() which is used for to check for a valid npassant move
 */
#include "newchess.h"
int npassant(chess *q, int n) {//Verifies if npassant is valid
	/* Check if the q->prevstate pawn is just moved 2 steps before doing the present npass */
	/* This can be done by checking the stack */
	int row, prrow, *prloc, valid, count = 0, counter = 0, i;
	if(q->state == WHITE) {
		row = 3;
		prrow = 1;
	}
	else {
		row = 4;
		prrow = 6;
	}
	prloc = pop(q, &q->s);
	push(q, &q->s, prloc, &prloc[4]);
	/* Got previous move */
	if(prloc[0] == PAWN && prloc[1] == prrow && prloc[5] == row) {
		for(i = -1; i < 2; i = i + 2) {
			if(((prloc[6] - 1  > -1 && q->p[row][prloc[6] - 1].name[1] == 'P' && q->p[row][prloc[6] - 1].color == q->state  && (prloc[2] -= 1) && count == 0 && (count = 1)) || (prloc[6] + 1 < 8 && q->p[row][prloc[6] + 1].name[1] == 'P' && q->p[row][prloc[6] + 1].color == q->state && (prloc[2] += 1) && (count == 0 || count == 1) && (count = 2)))) {
				if(row == 3 && (prloc[5] -= 1) || row == 4 && (prloc[5] += 1));
				prloc[7] = KILL;
				prloc[1] = row;
				q->p[prloc[1]][prloc[6]].name[0] = q->p[prloc[1]][prloc[6]].name[1] = '_';
				q->p[prloc[1]][prloc[6]].status = NOSTATUS;
				push(q, &q->s, prloc, &prloc[4]);
				q->s.tail->loc3 = (int *)malloc(sizeof(int) * 5);
				q->s.tail->loc3[0] = PAWN;
				q->s.tail->loc3[1] = prloc[1];
				q->s.tail->loc3[2] = prloc[6];
				q->s.tail->loc3[3] = NOKILL;
				q->s.tail->loc3[4] = q->prevstate;//Color
				q->s.tail->castle = NPASS;
				move1(q, prloc, &prloc[4], "no");
				valid = verifycheck(q);
				changestate(q);
				undoredo(q, "undo");
				if(valid == NOCHECK) {
					counter++;
				}
			}
		}
	}
	if(counter == 1) {
		prloc = pop(q, &q->s);
		push(q, &q->s, prloc, &prloc[4]);
		if(count == 1) {
			prloc[2] -= 1;
		}
		else {
			prloc[2] +=1;
		}
		if(row == 3 && (prloc[5] -= 1) || row == 4 && (prloc[5] += 1));
		prloc[7] = KILL;
		prloc[1] = row;
		q->p[prloc[1]][prloc[6]].name[0] = q->p[prloc[1]][prloc[6]].name[1] = '_';
		q->p[prloc[1]][prloc[6]].status = NOSTATUS;
		push(q, &q->s, prloc, &prloc[4]);
		q->s.tail->loc3 = (int *)malloc(sizeof(int) * 5);
		q->s.tail->loc3[0] = PAWN;
		q->s.tail->loc3[1] = prloc[1];
		q->s.tail->loc3[2] = prloc[6];
		q->s.tail->loc3[3] = NOKILL;
		q->s.tail->loc3[4] = q->prevstate;//Color
		q->s.tail->castle = NPASS;
		move1(q, prloc, &prloc[4], "no");
		return 1;
	}
	if(counter == 2) {
		prloc = pop(q, &q->s);
		push(q, &q->s, prloc, &prloc[4]);
		if(n == 0) {
			mvprintw(21, 110, "Ambiguity!");
			mvprintw(23, 110, "Please enter the previous location");
			while(1) {
				mvprintw(25, 110, "1. P%c%d or 2. P%c%d", 97 + (prloc[2] - 1), 8 - prloc[1] - 2,97 + (prloc[2] + 1), 8 - prloc[1] - 2);
				mvscanw(27, 117, "%d", &counter);
				if(counter == 1) {
					prloc[2] -= 1;
					break;
				}
				else if(counter == 2) {
					prloc[2] += 1;
					break;
				}
				else {
					printw("Please enter the correct input");
				}
			}
		}
		else {
			if(n == 2) {
				prloc[2] -= 1;
			}
			else {
				prloc[2] += 1;
			}
		}
		if(row == 3 && (prloc[5] -= 1) || row == 4 && (prloc[5] += 1));
		prloc[7] = KILL;
		prloc[1] = row;
		q->p[prloc[1]][prloc[6]].name[0] = q->p[prloc[1]][prloc[6]].name[1] = '_';
		q->p[prloc[1]][prloc[6]].status = NOSTATUS;
		push(q, &q->s, prloc, &prloc[4]);
		q->s.tail->loc3 = (int *)malloc(sizeof(int) * 5);
		q->s.tail->loc3[0] = PAWN;
		q->s.tail->loc3[1] = prloc[1];
		q->s.tail->loc3[2] = prloc[6];
		q->s.tail->loc3[3] = NOKILL;
		q->s.tail->loc3[4] = q->prevstate;//Color
		q->s.tail->castle = NPASS;
		move1(q, prloc, &prloc[4], "no");
		return 1;
	}  
	else {
		getch();
		return 0;
	}
} 

