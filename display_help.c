
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

/*This file is used to display help and about related to the game
 */
#include "newchess.h"
int display_help_about(WINDOW *win, char *str) {
	int fdr, x;
	char c;
	clear();
	init_pair(11, COLOR_BLACK, COLOR_WHITE); 
	bkgd(COLOR_PAIR(11));
	if(strcmp(str, "help") == 0) {
		fdr = open("help.txt", O_RDONLY);
	}
	else {
		fdr = open("about.txt", O_RDONLY);
	}
	if(fdr == -1) {
		printw("Error opening the file");
		refresh();
		getch();
		return 0;
	}
	while((x = read(fdr, &c, 1))) {
		printw("%c", c);
	}
	refresh();
	getch();
	return 0;
}
