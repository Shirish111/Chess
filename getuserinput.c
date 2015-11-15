
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

/*This file contains the function getuserinput() which gets the input from the user and returns the string 
 */
#include "newchess.h"
char *getuserinput(WINDOW *win) {
	char *s;
	s = (char *)malloc(16);
	curs_set(1);
	mvwprintw(win, 14, 110, "Enter your move\n");
	mvwaddch(win, 14, 126, ':');
	mvwscanw(win, 14, 128, "%s", s);
	curs_set(0);
	if(strlen(s) < 2) {
		return NULL;
	}
	return s;
}
