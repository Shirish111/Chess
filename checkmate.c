
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

#include "newchess.h"
/* 1. Verify check for king's adjacent locations */
/* 1.2.1 If there is a check and the checkgiver count == 2 then directly say checkmate! */
/* 1.2.2.1 If there is a check and the checkgiver count != 2 then find if you can kill the checkgiver */
/* 1.2.2.2 If no see if you can put any piece in between the checkgiver and the king to act as a barrier and if this also fails then checkmate! */
int checkmate(chess *q) {
	int *kingloc, *newlocation, *prloc, i, j, iadd, jadd, idiff, jdiff, name, valid, k, l;
	chg *tmp;
	tmp = (chg*) malloc (sizeof(chg));
	newlocation = (int *) malloc (sizeof(int) * 4);
	kingloc = search(q, KING, q->state, NULL, NULL);
	i = kingloc[1];
	j = kingloc[2];
	for(k = 0; k < 4; k++) 
		*tmp = q->c;/* Copying structure of checkgiver */
	name = tmp->a[0];
	newlocation[0] = kingloc[0];
	for(iadd = -1; iadd < 2; iadd++) {/* Verifies if the king can be placed at surrounding positions without a check */
		if((i + iadd > -1) && (i + iadd < 8)) {
			newlocation[1] = i + iadd;
			for(jadd = -1; jadd < 2; jadd++) {
				if((j + jadd > -1) && (j + jadd < 8)) {
					if(iadd == 0 && jadd == 0) {/* Because it is the old location itself */
						continue;
					}
					newlocation[2] = j + jadd;
					if(q->p[newlocation[1]][newlocation[2]].status == ALIVE && q->p[newlocation[1]][newlocation[2]].color == q->state) {
						continue;
					}
					else if(q->p[newlocation[1]][newlocation[2]].status == ALIVE) {
						newlocation[3] = KILL;
					}
					else {
						newlocation[3] = NOKILL;
					}
					printstate(stdscr, q);
					push(q, &q->s, kingloc, newlocation);
					move1(q, kingloc, newlocation, "exp");
					valid = verifycheck(q);
					changestate(q);
					undoredo(q, "undowithoutredo");
					if(valid == NOCHECK) {
						free(tmp);
						return NOCHECKMATE;
					}
				}
			}
		}
	}
	/* Assertion :Now if you just move the king you will definitely get a CHECK */
	if(tmp->count == 2) {
		free(tmp);
		return CHECKMATE;
	}
	/* Assertion :Only one checkgiver */
	/* Now trying to kill the checkgiver */
	tmp->a[3] = KILL;
	printstate(stdscr, q);
	prloc = pawnsearch(q, tmp->a);
	if(prloc[0] != NOTFOUND) {
		push(q, &q->s, prloc, tmp->a);
		move1(q, prloc, tmp->a, "exp");
		valid = verifycheck(q);
		changestate(q);
		undoredo(q, "undowithoutredo");
		if(valid == NOCHECK) {
			free(tmp);
			return NOCHECKMATE;
		}
	}
	tmp->a[3] = KILL;
	for(i = KNIGHT; i < KING; i++) {
		tmp->a[0] = i;
		prloc = getpreviousloc(q, tmp->a, 0);
		if(prloc) {
			prloc = checkifvalid(q, tmp->a, prloc, 0);
			if(prloc) {
				push(q, &q->s, prloc, tmp->a);
				move1(q, prloc, tmp->a, "exp");
				valid = verifycheck(q);
				changestate(q);
				undoredo(q, "undowithoutredo");
				if(valid == NOCHECK) {
					free(tmp);
					return NOCHECKMATE;
				}
			}
		}
	}
	tmp->a[0] = name;
	/* Assertion : You can't kill the checkgiver */
	/* Now see if you can put other piece as a barrier in between the checkgiver and the KING */
	if(name == KNIGHT) {/* Because you can't put a barrier for a knight */
		free(tmp);
		return CHECKMATE;
	}
	idiff = tmp->a[1] - kingloc[1];
	jdiff = tmp->a[2] - kingloc[2];
	if(idiff > 0 && (iadd = 1) || idiff < 0 && (iadd = -1) || idiff == 0 && (iadd = 0));
	if(jdiff > 0 && (jadd = 1) || jdiff < 0 && (jadd = -1) || jdiff == 0 && (jadd = 0));
	for(((i = kingloc[1] + iadd) , (j = kingloc[2] + jadd)); (((idiff > 0 && i < tmp->a[1]) || (idiff < 0 && i > tmp->a[1])  || (idiff == 0 && i == kingloc[1])) && ((jdiff > 0 && j < tmp->a[2]) || (jdiff < 0 && j > tmp->a[2])  || (jdiff == 0 && j == tmp->a[2]))); ((i += iadd) , (j += jadd))) {
		newlocation[0] = PAWN;
		newlocation[1] = i;
		newlocation[2] = j;
		if(q->p[i][j].status == ALIVE) {
			newlocation[3] = KILL;
		}
		else {
			newlocation[3] = NOKILL;
		}
		prloc = pawnsearch(q, newlocation);

		if(prloc[0] != NOTFOUND) {
			push(q, &q->s, prloc, newlocation);
			move1(q, prloc, newlocation, "exp");
			valid = verifycheck(q);
			changestate(q);
			undoredo(q, "undowithoutredo");
			if(valid == NOCHECK) {
				free(tmp);
				return NOCHECKMATE;
			}
		}
		for(k = KNIGHT; k < KING; k++) {
			newlocation[0] = k;
			prloc = getpreviousloc(q, newlocation, 0);
			if(prloc) {
				prloc = checkifvalid(q, newlocation, prloc, 0);
				if(prloc) {
					newlocation[0] = prloc[0];
					push(q, &q->s, prloc, newlocation);
					move1(q, prloc, newlocation, "exp");
					valid = verifycheck(q);
					changestate(q);
					undoredo(q, "undowithoutredo");
					if(valid == NOCHECK) {
						free(tmp);
						return NOCHECKMATE;
					}
				}
			}
		}
	}
	/* Assertion : Now we can say that it is really a checkmate */
	return CHECKMATE;
}

