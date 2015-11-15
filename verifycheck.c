
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

/*This file contains two functions verifycheck() which is used to verify if there is a check and copyloc() which copies the location of checkgiver in another location
 */
#include "newchess.h"
int verifycheck(chess *q) {
	int *prloc, valid;
	prloc = (int *)malloc(sizeof(int) * 4);
	prloc = search(q, KING, q->state, NULL, NULL);/* Searches from the list gets returns the location */
	valid = checkfrompawns(q, prloc);/* Verify if there is a CHECK from pawns */
	if(valid == CHECK) {
		return CHECK;
	}
	valid = checkfromall(q, prloc);/* Verify if there is a CHECK from all pieces (except pawns) */
	if(valid == CHECK) {
		return CHECK;
	}
	return NOCHECK;
}
void copyloc(chg *c, int *loc) {
	int i;
	for(i = 0; i < 4; i++) {
		c->a[i] = loc[i];
	}
}
