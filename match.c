
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

/*This file includes the match() function which verifies for a match between the previous and the next location
 */
#include "newchess.h"
int match(chess *q, int *prloc, int *locinput) {
	int i, j;
	switch(locinput[0]) {
		case ROOK:
			if(locinput[1] == prloc[1] || locinput[2] == prloc[2]) {
				return 1;/* Matched */
			}
			return 0;/* Not matched */
			break;
		case BISHOP:
			i = locinput[1] - prloc[1];
			j = locinput[2] - prloc[2];
			if(i == j || i == -j) {
				return 1;
			}
			return 0;
			break;
		case QUEEN:
			if(locinput[1] == prloc[1] || locinput[2] == prloc[2]) {
				return 1;
			}
			i = locinput[1] - prloc[1];
			j = locinput[2] - prloc[2];
			if((i == j || i == -j)) {
				return 1;
			}
			return 0;
			break;
		case KNIGHT:
			i = locinput[1] - prloc[1];
			j = locinput[2] - prloc[2];
			if(i < 3 && i > -3 && j < 3 && j > -3) {
				if(i + j == 3 || i - j == 3 || -i + j == 3 || -i -j == 3) {
					if(i != 0 && j != 0) {
						return 1;
					}
				}
			}
			return 0;
			break;
		case KING:
			if((prloc[1] + 1 == locinput[1] || prloc[1] == locinput[1] || prloc[1] - 1 == locinput[1]) && (prloc[2] + 1 == locinput[2] || prloc[2] == locinput[2] || prloc[2] - 1 == locinput[2])) {
				return 1;
			}
			return 0;
			break;
	}
}
