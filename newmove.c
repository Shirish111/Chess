
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

/*This file contains two functions move1 and castlemove()
 *move1() function is used for moving the pieces on the board
 *castlemove() is used to move for a castling
 */
#include "newchess.h"
#include <string.h>
void move1(chess *q, int *prloc, int *locinput, char *str) {
	int *killedpiece;
	int a, i;
	if((((locinput[3] == NOKILL) && (strcmp(str, "undo") != 0 && strcmp(str, "undowithoutredo") != 0))) || (((prloc[3] == NOKILL) && (strcmp(str, "undo") == 0 || strcmp(str, "undowithoutredo") == 0)))){
		if(locinput[0] != PAWN) {
			update(q, prloc, locinput);/* Because it will change its position */
		}
		/* For normal case we are putting the piece on new location */
		/* For undo case we are putting the piece on old location */ 
		q->p[locinput[1]][locinput[2]].name[1] = rconvertp(locinput[0]);
		q->p[locinput[1]][locinput[2]].name[0] = concolor(q->state);
		q->p[locinput[1]][locinput[2]].status = ALIVE;
		q->p[locinput[1]][locinput[2]].color = q->state;
		/* For normal case we are making the old location as empty */
		/* For undo case we are making the new location empty */
		q->p[prloc[1]][prloc[2]].name[0] = q->p[prloc[1]][prloc[2]].name[1] = '_';
		q->p[prloc[1]][prloc[2]].status = NOSTATUS;
		q->p[prloc[1]][prloc[2]].color = NOCOLOR;
		if(strcmp(str, "undo") == 0 || strcmp(str, "undowithoutredo") == 0) {
			q->p[locinput[1]][locinput[2]].name[0] = concolor(q->prevstate);
			q->p[locinput[1]][locinput[2]].color = q->prevstate;
			/* Done with prloc not for undo */
		}
		else if(strcmp(str, "redo") == 0) {
			q->p[locinput[1]][locinput[2]].name[0] = concolor(q->state);
			q->p[locinput[1]][locinput[2]].color = q->state;
		}
		else {
			/* free redo */
			if(empty(&q->r) == 0 && strcmp(str, "exp") != 0) {
				freeredo(q, &q->r);
			}
		}
	}
	else {/* KILL */
		/* For the piece being killed */
		a = convertp(q->p[locinput[1]][locinput[2]].name[1]); /* Converts char into int */
		if(a != PAWN) {
			killedpiece = (int *)malloc(sizeof(int) * 4);
			killedpiece[0] = a;
			killedpiece[1] = locinput[1];
			killedpiece[2] = locinput[2];
			killedpiece[3] = NOKILL;
			remov(q, killedpiece);/* The piece will be removed from the list   */
			free(killedpiece);
		}
		if(locinput[0] != PAWN) {
			update(q, prloc, locinput);/* Because it is changing its position */
		}
		/* Everything about killedpiece is done and now about moving */
		if((strcmp(str, "undo") == 0) || (strcmp(str, "redo") == 0) || (strcmp(str, "undowithoutredo") == 0)) {
			q->p[locinput[1]][locinput[2]].name[1] = rconvertp(locinput[0]);
			q->p[locinput[1]][locinput[2]].status = ALIVE;
			if(strcmp(str, "undo") == 0 || strcmp(str, "undowithoutredo") == 0) {
				q->p[locinput[1]][locinput[2]].name[0] = concolor(q->prevstate);
				q->p[locinput[1]][locinput[2]].color = q->prevstate;
			}
			else {
				q->p[locinput[1]][locinput[2]].name[0] = concolor(q->state);
				q->p[locinput[1]][locinput[2]].color = q->state;
			}
			/* Done with prloc not for undo */
			/* Restoring the killed piece */
			if(strcmp(str, "undo") == 0 || strcmp(str, "undowithoutredo") == 0) {
				q->p[prloc[1]][prloc[2]].name[0] = concolor(q->state);
				q->p[prloc[1]][prloc[2]].name[1] = rconvertp(prloc[4]);
			}
			else {
				q->p[prloc[1]][prloc[2]].name[0] = '_';
				q->p[prloc[1]][prloc[2]].name[1] = '_';
			}
			q->p[prloc[1]][prloc[2]].status = ALIVE;
			q->p[prloc[1]][prloc[2]].color = prloc[8];
		}
		else {
			/* free redo */
			if(empty(&q->r) == 0 && strcmp(str, "exp") != 0) {
				freeredo(q, &q->r);
			}
			update(q, prloc, locinput);
			q->p[prloc[1]][prloc[2]].name[0] = q->p[prloc[1]][prloc[2]].name[1] = '_';
			q->p[prloc[1]][prloc[2]].status = NOSTATUS;
			q->p[prloc[1]][prloc[2]].color = NOCOLOR;
			q->p[locinput[1]][locinput[2]].name[1] = rconvertp(locinput[0]);/* Converts int to char */
			q->p[locinput[1]][locinput[2]].name[0] = concolor(q->state);
			q->p[locinput[1]][locinput[2]].status = ALIVE;
			q->p[locinput[1]][locinput[2]].color = q->state;
			if(locinput[0] != PAWN) {
				update(q, prloc, locinput);
			}
		}
	}  
}
void castlemove(chess *q, int *kingloc, int *rookloc) {
	int *newkingloc, *newrookloc, i;
	newkingloc = (int *)malloc(sizeof(int) * 4);
	newrookloc = (int *)malloc(sizeof(int) * 4);
	newrookloc[3] = NOKILL;
	newkingloc[3] = NOKILL;
	newrookloc[0] = rookloc[0];
	newkingloc[0] = kingloc[0];
	q->p[kingloc[1]][kingloc[2]].name[0] = q->p[kingloc[1]][kingloc[2]].name[1] = '_';
	q->p[kingloc[1]][kingloc[2]].status = NOSTATUS;
	if(kingloc[2] - rookloc[2] == 3 || kingloc[2] - rookloc[2] == -3) {/* Short castle */
		newkingloc[1] = kingloc[1];
		newkingloc[2] = rookloc[2] - 1;
		newrookloc[1] = rookloc[1];
		newrookloc[2] = kingloc[2] + 1;

	}
	else {/* long castle */
		newkingloc[1] = kingloc[1];
		newkingloc[2] = rookloc[2] + 2;
		newrookloc[1] = rookloc[1];
		newrookloc[2] = kingloc[2] - 1;
	}
	push(q, &q->s, kingloc, newkingloc);
	move1(q, kingloc, newkingloc, "no");
	push(q, &q->s, rookloc, newrookloc);
	move1(q, rookloc, newrookloc, "castle");
	q->s.tail->castle = CASTLE;
	free(newkingloc);
	free(newrookloc);
}
