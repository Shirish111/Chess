
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

/*This file includes the function savefile() which is used to save the moves played in the game
 */
#include "newchess.h"
void savefile(chess *q) {
	/* Copying to other file */
	int fdr, x, n;
	char c, s[128];
	FILE *fdw;
	clear();
	init_pair(11, COLOR_BLACK, COLOR_WHITE); 
	bkgd(COLOR_PAIR(11));
	mvprintw(LINES / 2 - 2, COLS / 2 - 16, "Please enter the filename(Enter -1 to skip) : ");
	scanw("%s", s);
	if(strcmp(s, "-1") == 0) {
		mvprintw(LINES / 2 + 2, COLS / 2 - 8, "FILE NOT SAVED");
		refresh();
		getch();
		if(q->enable == ENABLE) {
			display(stdscr, q);
		}
		q->enable = ENABLE;
		return;
	}
	fdw = fopen(s, "w");
	if(fdw == NULL) {
		printf("Error\n");
		exit(1);
	}
	fdr = open("MovesList1.txt", O_RDONLY, S_IRWXU);
	if(fdr == -1) {
		printw("Error opening the file MovesList.txt\n");
		exit(1);
	}
	while(1) {
		x = read(fdr, &n, sizeof(int));
		if(x == 0 || x == -1) {
			break;
		}
		// printw("%d", n);
		fprintf(fdw, "%d", n);
		x = read(fdr, &c, 1);
		if(x == 0 || x == -1) {
			break;
		}
		//printw("%c", c);
		fprintf(fdw, "%c", c);
		x = read(fdr, &c, 1);
		if(x == 0 || x == -1) {
			break;
		}
		//fprintf(fdr, "%c", c);
		while(c != '\0') {
			//printw("%c", c);
			fprintf(fdw, "%c", c);
			x = read(fdr, &c, 1);
			if(x == 0 || x == -1) {
				return;
			}
		}
		x = read(fdr, &c, 1);
		if(x == 0 || x == -1) {
			break;
		}
		//printw("%c", c);

		fprintf(fdw, "%c", c);
		if(c == '+') {
			fprintf(fdw, "%c", ' ');
		}
	}
	fclose(fdw);
	mvprintw(LINES / 2 + 2, COLS / 2 - 8, "Saved Successfully");
	refresh();
	if(q->enable == ENABLE) {
		getch();
		display(stdscr, q);
	}
	q->enable = ENABLE;
}
