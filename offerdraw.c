
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

/* This file includes the functions offerdraw which is used to ask the user if he wants to draw
 */
#include "newchess.h"
int offerdraw(chess *q) {
	int n;
	mvprintw(29, 110, "Offer draw");
	mvprintw(29, 110, "1. Accept 2. Reject");
	mvscanw(30, 115, "%d", &n);
	if(n == 1) {
		declaredraw(q," ");
		return 1;
	}
	return 0;
}
