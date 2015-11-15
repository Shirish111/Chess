
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

/*This file contains checkfrompawns function which is used to verify if there is a check from any pawn
 */
#include "newchess.h"
/*kingloc[1] = ith row
  kingloc[2] = jth column
 */
int checkfrompawns(chess *q, int *kingloc) {
	int row;
	if((kingloc[1] < 2) && (q->state == WHITE)) {
		return NOCHECK;
	}
	if((kingloc[1] > 5) && (q->state == BLACK)) {
		return NOCHECK;
	}
	if(q->state == WHITE) {
		row = -1;
	}
	else {
		row = 1;
	}
	if(kingloc[2] != 0 && kingloc[2] != 7) {/* For left and right corners */
		if(((q->p[kingloc[1] + row][kingloc[2] - 1].name[1] == 'P' && q->p[kingloc[1] + row][kingloc[2] - 1].color == q->prevstate)) || ((q->p[kingloc[1] + row][kingloc[2] + 1].name[1] == 'P' && q->p[kingloc[1] + row][kingloc[2] + 1].color == q->prevstate))) {
			if(q->enable == ENABLE) {
				mvprintw(22, 110, "CHECK from PAWN");	
			}
			return CHECK;
		}
	}
	else if(kingloc[2] == 0) {
		if((q->p[kingloc[1] + row][kingloc[2] + 1].name[1] == 'P' && q->p[kingloc[1] + row][kingloc[2] + 1].color == q->prevstate)) {
			if(q->enable == ENABLE) {
				mvprintw(22, 110, "CHECK from PAWN");	
			}
			return CHECK;
		}
	}
	else {/* kingloc[2] = 7 */
		if((q->p[kingloc[1] + row][kingloc[2] - 1].name[1] == 'P' && q->p[kingloc[1] + row][kingloc[2] - 1].color == q->prevstate)) {
			if(q->enable == ENABLE) {
				mvprintw(22, 110, "CHECK from PAWN");	
			}
			return CHECK;
		}
	}
	return NOCHECK;	
}
