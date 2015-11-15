
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

/*This file is used to just check the barrier between the locations
 */
#include "newchess.h"
int simplebarrier(chess *q, int *loc1, int *loc2) {//Checks if there are any coins placed between the two locations
	int idiff, jdiff, i, j, diff, iadd, jadd;
	idiff = loc2[1] - loc1[1];
	jdiff = loc2[2] - loc1[2];
	if(idiff == jdiff || idiff == -jdiff) {//Bishop like cross way
		if(((idiff > 0 && (iadd = -1)) || (idiff < 0 && (iadd = +1))) && ((jdiff > 0 && (jadd = -1)) || (jdiff < 0 && (jadd = +1)))) {
			for(((i = loc2[1] + iadd) && (j = loc2[2] + jadd)); ((((i > loc1[1]) && (idiff > 0)) || ((i < loc1[1]) && (idiff < 0))) && (((j > loc1[2]) && (jdiff > 0)) || ((j < loc1[2]) && (jdiff < 0)))); ((i = i + iadd) && (j = j + jadd))) {
				if(q->p[i][j].status == ALIVE) {
					return 1;
				}
			}
			return 0;
		}
		else {//If none is matching
			return 1;
		}
	}
	else if(idiff == 0 || jdiff == 0) {//Rook like way
		if(loc2[1] == loc1[1]) {//i is matching Done
			/* printf("idiff in simplebarrier\n"); */
			diff = loc1[2] - loc2[2];//diff can't be 0 (case 0 gets eliminated in correctness()),> then loc1 is to the left of loc2, < loc1 is to the right of loc2
			if(((diff > 0 && (jadd = 1)) || (diff < 0 && (jadd = -1)))) {
				for(j = loc2[2] + jadd; ((diff < 0) && (j > loc1[2])) || ((diff > 0) && (j < loc1[2])); j = j + jadd) {
					if(q->p[loc2[1]][j].status == ALIVE) {
						/* for(i = 0; i < 4; i++) { */
						/*   printf("loc2[1] = %d j %d\n", loc2[1], j); */
						/* } */
						return 1;
					}
				}
				return 0;
			}
		}
		else if(loc2[2] == loc1[2]) {//j is matching(Both can't match at the same time)
			diff = loc2[1] - loc1[1];
			if((diff > 0 && (iadd = -1)) || (diff < 0 && (iadd = +1))) {
				for(j = loc2[1] + iadd; (((j < loc1[1]) && (diff < 0)) || ((j > loc1[1]) && (diff > 0)));j = j + iadd) {
					if(q->p[j][loc2[2]].status == ALIVE) {
						return 1;
					}
				}
				return 0;
			}
		}
		else {//If none is matching
			return 1;
		}
	}
	else {
		return 0;
	}
}
