
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

/*This file contains the function convprint() which modifies the printing of the location
 */
#include "newchess.h"
void convprint(int *loc) {
	int i;
	for(i = 0; i < 4; i++) {
		switch(loc[i]) {
			case PAWN:
				printf("PAWN\n");
				break;
			case KNIGHT:
				printf("KNIGHT\n");
				break;
			case BISHOP:
				printf("BISHOP\n");
				break;
			case KING:
				printf("KING\n");
				break;
			case QUEEN:
				printf("QUEEN\n");
				break;
			case ROOK:
				printf("ROOK\n");
				break;
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
				if(i == 0) {
					printf("PAWN\n");
				}
				if(i == 1) {
					printf("i = %d\n", loc[i]);
				}
				if(i == 2) {
					printf("j = %d\n", loc[i]);
				}
				break;
			case NOKILL:
				printf("NOKILL\n");
				break;
			case KILL:
				printf("KILL\n");
				break;
		}
	}
}
