
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
int castling(chess *q, char *str) {
	/* Check if str is 0-0 or 0-0-0 */
	/* get the location of king */
	/* Check if King has been moved in this game */
	/* If not moved and 0-0, */
	/* check if at a distance of 4 and in the same row if there is a rook and it also has not been moved */
	/* if this is also true then check if there is a barrier between the king and the rook */
	/* if there is no barrier then verify if there can be a check if the king is placed in one of the boxes 	between the king and the rook */
	/* if no check then it is valid */
	/* in case of 0-0-0 just change the distance to 5 and repeat the same steps */
	int moved1 = -1, moved2 = -1, valid;
	int *kingloc, *newkingloc;
	int *rookloc, j, jadd, jdiff;
	valid = verifycheck(q);
	if(valid == CHECK) {
		return 0;
	}
	newkingloc = (int *) malloc(sizeof(int ) *4);
	kingloc = search(q, KING, q->state, &moved1, &moved2);/* Gets the location of king */
	if(moved1 == MOVED || moved2 == MOVED) {
		mvprintw(25, 110, "King moved\n");
		getch();
		return 0;
	}
	rookloc = search(q, ROOK, q->state, &moved1, &moved2);
	if(moved1 == MOVED || moved2 == MOVED) {
		mvprintw(25, 110, "Rook already moved"); 
		return 0;
	}
	if(moved1 != MOVED && (((strcmp(str, "0-0") == 0) && ((kingloc[2] - rookloc[2] == 3) || (kingloc[2] - rookloc[2] == -3))) || ((strcmp(str, "0-0-0") == 0) && ((kingloc[2] - rookloc[2] == 4) || (kingloc[2] - rookloc[2] == -4))))) {
		valid = simplebarrier(q, rookloc, kingloc);
		if(valid == 0) {/* If no barrier then */
			/* verify check for locations between king and rook */
			/* Put the king in the location and verifycheck and do it for all places in between */
			/* If there is no check then do castling */
			jdiff = kingloc[2] - rookloc[2];/* Since idiff should be zero as both the pieces are not moved */
			if((jdiff > 0 && (jadd = -1)) || (jdiff < 0 && (jadd = 1)));
			newkingloc[0] = kingloc[0];
			newkingloc[1] = kingloc[1];
			newkingloc[3] = NOKILL;
			for(j = kingloc[2] + jadd; ((jdiff > 0 && (j > rookloc[2])) || (jdiff < 0 && (j < rookloc[2]))); j += jadd) {
				newkingloc[2] = j;
				push(q, &q->s, kingloc, newkingloc);
				move1(q, kingloc, newkingloc, "no");
				valid = verifycheck(q);
				changestate(q);
				undoredo(q, "undo");
				if(valid == CHECK) {
					mvprintw(25, 110, "There is a check in the way");
					getch();
					return 0;
				}
			}
			/* Do castling */
			castlemove(q, kingloc, rookloc);
			return 1;

		}
		else {
			mvprintw(25, 110, "Barrier in between\n");
			getch();
			return 0;
		}
	}
	else if(moved2 != MOVED && (((strcmp(str, "0-0") == 0) && ((kingloc[2] - rookloc[6] == 3) || (kingloc[2] - rookloc[6] == -3))) || ((strcmp(str, "0-0-0") == 0) && ((kingloc[2] - rookloc[6] == 4) || (kingloc[2] - rookloc[6] == -4))))) {
		valid = simplebarrier(q, &rookloc[4], kingloc);
		if(valid == 0) {/* If no barrier then */
			/* verify check for locations between king and rook */
			/* Put the king in the location and verifycheck and do it for all places in between */
			/* If there is no check then do castling */
			jdiff = kingloc[2] - rookloc[6];/* Since idiff is zero as both the pieces are not moved */
			if((jdiff > 0 && (jadd = -1)) || (jdiff < 0 && (jadd = 1)));
			newkingloc[0] = kingloc[0];
			newkingloc[1] = kingloc[1];
			newkingloc[3] = NOKILL;
			for(j = kingloc[2] + jadd; ((jdiff > 0 && (j > rookloc[6])) || (jdiff < 0 && (j < rookloc[6]))); j += jadd) {
				newkingloc[2] = j;
				push(q, &q->s, kingloc, newkingloc);
				move1(q, kingloc, newkingloc, "no");
				valid = verifycheck(q);
				changestate(q);
				undoredo(q, "undo");
				if(valid == CHECK) {
					mvprintw(25, 110, "There is a CHECK in the way");
					getch();
					return 0;
				}
			}
			/* Do castling */
			castlemove(q, kingloc, &rookloc[4]);
			return 1;
		}
		else {
			mvprintw(25, 110, "Barrier in between");
			return 0;
		}
	}
	else {
		return 0;
	}
}
