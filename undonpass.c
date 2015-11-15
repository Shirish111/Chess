
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

/*This file includes the functions undonpass and redonpass which is used to undo and redo the npass move
 */
#include "newchess.h"
void undonpass(chess *q) {
	int *loc;
	loc = pop(q, &q->s);
	q->p[loc[1]][loc[2]].name[0] = concolor(q->prevstate);
	q->p[loc[1]][loc[2]].name[1] = 'P';
	q->p[loc[1]][loc[2]].status = ALIVE;
	q->p[loc[1]][loc[2]].color = q->prevstate;
	q->p[loc[5]][loc[6]].name[0] = q->p[loc[5]][loc[6]].name[1] = '_';
	q->p[loc[5]][loc[6]].status = NOSTATUS;
	q->p[loc[5]][loc[6]].color = NOCOLOR;
	q->p[loc[9]][loc[10]].name[0] = concolor(q->state);
	q->p[loc[9]][loc[10]].name[1] = 'P';
	q->p[loc[9]][loc[10]].color = q->state;
	q->p[loc[9]][loc[10]].status = ALIVE;
	changestate(q);
	push(q, &q->r, &loc[4], loc);
	q->r.tail->castle = NPASS;
}
void redonpass(chess *q) {
	int *loc;
	loc = pop(q, &q->r);
	if(loc[2] == loc[6] - 1) {
		npassant(q, 3);
	}
	else {
		npassant(q, 2);
	}
	changestate(q);
}
