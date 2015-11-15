
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

/*This file includes the functions undoredo() which is used for undo and redo operations
 */
#include "newchess.h"
#include <string.h>
//loc[4] = locinput loc[0] = prloc
int *undoredo(chess *q, char *str) {
	int *loc, i, counter = 0;
	if((strcmp(str, "undo") == 0) && (empty(&q->s) == 0) && (q->s.tail->castle == NPASS)) {
		undonpass(q);
		return;
	}
	else if((strcmp(str, "redo") == 0) && (empty(&q->r) == 0) && (q->r.tail->castle == NPASS)) {
		redonpass(q);
		return;
	}
	else if((strcmp(str, "undo") == 0) && (empty(&q->s) == 0) && (q->s.tail->castle == CASTLE)) {
		counter = 1;
	} 
	else if((strcmp(str, "redo") == 0) && (empty(&q->r) == 0) && (q->r.tail) && (q->r.tail->castle == CASTLE)) {
		counter = 2;
	}
	if((strcmp(str, "undo") == 0) || (strcmp(str, "undowithoutredo") == 0)) {
		loc = pop(q, &q->s);
	}

	else {
		loc = pop(q, &q->r);
	}
	if(counter == 1) {
		undoredo(q, "undo");
		changestate(q);
	}
	else if(counter == 2) {
		undoredo(q, "redo");
		changestate(q);
	}
	if(loc) {
		if(strcmp(str, "undo") == 0) {
			push(q, &q->r, &loc[4], loc);
			if(counter == 1) {
				q->r.tail->castle = CASTLE;
			}
		}
		else if(strcmp(str, "undowithoutredo") == 0) {
			move1(q, &loc[4], loc, "undowithoutredo");
		}
		else {
			push(q, &q->s, &loc[4], loc);
			if(counter == 2) {
				q->s.tail->castle = CASTLE;
			}
		}
		if(strcmp(str, "undowithoutredo") != 0) {
			move1(q, &loc[4], loc, str);
		}
		if(strcmp(str, "redo") == 0) {
			unmove(q, &loc[4], "move");
		}
		else {
			unmove(q, loc, "unmove");
		}
	}
	changestate(q);
	return loc;
}
