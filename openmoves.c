
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

/*This file contains a function which is used to open a previously saved file (containing moves)
 */
#include "newchess.h"
void openmoves(chess *q) {
	int fdr;
	int i = 1, x, n;
	int j = 0;
	char c = '\t', s[128];
	clear();
	init_pair(11, COLOR_BLACK, COLOR_WHITE); 
	bkgd(COLOR_PAIR(11));
	printw("Please enter the filename : ");
	scanw("%s", s);
	if(i == 1) {
		fdr = open(s, O_RDONLY, S_IRWXU);
		if(fdr == -1) {
			printw("Error opening the file\n");
			refresh();
			getch();
			display(stdscr, q);
			return;
		}
	}
	while((x = read(fdr, &c, 1))) {
		printw("%c", c);
	}
	refresh();
	getch();
	display(stdscr, q);
}
