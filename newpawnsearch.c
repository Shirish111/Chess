
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

/*This file contains the function pawnsearch() which searches for the location of pawn and returns the previous location.
 */
#include "newchess.h"
int *pawnsearch(chess *q, int *locinput) { 
	int *prloc, row = 0, j = locinput[2], i, counter, m;
	prloc = (int*) malloc (sizeof(int) * 4);
	for(i = 0; i < 4; i++) {
		prloc[i] = NOTFOUND;//Initialize to NOTFOUND
	}
	int confusion = 0;
	if(q->state == WHITE) {//Search down if white
		counter = 1;
	}
	else {//Search up if black
		counter = -1;
	}
	row = locinput[1];
	if(locinput[3] == NOKILL) {//Search in j
		for(i = 0; i < 2; i++) {
			row = row + counter;
			if(q->p[row][j].status == ALIVE) {
				if(q->p[row][j].name[1] == 'P' && q->p[row][j].color == q->state) {
					prloc[0] = PAWN;
					prloc[1] = row;
					prloc[2] = j;
					prloc[3] = NOKILL;
					break;
				}
				else {
					break;
				}
			}
			if(locinput[1] == 4 && counter == 1) {// 2 steps from starting position
				continue;
			}
			if(locinput[1] == 3 && counter == -1) {//2 steps from starting position
				continue;
			}
			else {
				break;
			}
		}
	}
	else {//KILL (i.e. X is included in the locinput)
		row = row + counter;
		for(m = -1; m < 2; m = m + 2) {
			j = locinput[2] + m;//Look in the two js adjacent to j
			if(q->p[row][j].status == ALIVE) {
				if(q->p[row][j].name[1] == 'P' && q->p[row][j].color == q->state) {
					if(confusion == 0) {
						prloc[0] = PAWN;
						prloc[1] = row;
						prloc[2] = j;
						prloc[3] = NOKILL;
						confusion = 1;
					}
					else {//If there are two possibilities
						for(i = 0; i < 4; i++) {
							prloc[i] = CONF;
						}
						confusion = 1;
					}
				}
			}
		}
	}
	return prloc;
}
