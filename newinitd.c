
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

/* This file contains functions init(), display1(), display2(),  display() and printcoinw()
 * init() is used for initialization of the chess board
 * All other functions are used for displaying
 */
#include "newchess.h"
void init(chess *q) {
	int fdr, i = 0, j = 0, k;
	coin a;
	//pawn, knight, bishop, rook, queen, king
	const int pevals[12][8][8] = {{{0,   0,   0,   0,   0,   0,   0,   0},
		{20,  20,  20,  20,  20,  20,  20,  20},
		{0,   0,   0,   0,   0,   0,   0,   0},
		{0,   0,   0,   40,  40,  0,   0,   0},
		{0,   0,   0,   40,  40,  0,   0,   0},
		{0,   0,   10,  30,  30, -10,  0,  -10},
		{20,  20,  20,  10,  10,  20,  20,  20},
		{0,   0,   0,   0,   0,   0,   0,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,  10,  10,   0,   0,   0},
		      {0,   0,  10,  40,  40,  10,   0,   0},
		      {0,   0,  10,  40,  40,  10,   0,   0},
		      {0,   0,  20,   0,   0,  20,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,  40,   0,   0,   0,   0,   0},
		      {0,   0,   0,  40,  40,   0,   0,   0},
		      {0,  20,   0,   0,   0,   0,  20,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {20,  20,  20,  20,  20,  20,  20,  20}, 
		      {0,   0,   0,   0,   0,   0,   0,   0}, 
		      {0,   0,   0,   0,   0,   0,   0,   0}, 
		      {0,   0,   0,   0,   0,   0,   0,   0}, 
		      {0,   0,   0,   0,   0,   0,   0,   0}, 
		      {10,  10,  10,  10,  10,  10,  10,  10},
		      {20,  20,  20,  20,  20,  20,  20,  20}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,  20,  30,  30,   0,   0,   0},
		      {0,   0,   0,  50,  30,   0,   0,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0}, 
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,  20,  50,  30,  50,   0, 100,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {20,  20,  20,  20,  20,  20,  20,  20},
		      {0,   0,  10,  30,  30, -10,   0, -10},
		      {0,   0,   0,  40,  40,   0,   0,   0},
		      {0,   0,   0,  40,  40,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {20,  20,  20,  10,  10,  20,  20,  20},
		      {0,   0,   0,   0,   0,   0,   0,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,  20,  10,  10,  20,   0,   0},
		      {0,   0,  10,  40,  40,  10,   0,   0},
		      {0,   0,  10,  40,  40,  10,   0,   0},
		      {0,   0,   0,  10,  10,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {0,  20,   0,   0,   0,   0,  20,   0},
		      {0,   0,   0,  40,  40,   0,   0,   0},
		      {0,   0,  40,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0}},
	      {{0,   0,   0,   0,   0,   0,   0,   0},
		      {20,  20,  20,  20,  20,  20,  20,  20},
		      {10,  10,  10,  10,  10,  10,  10,  10},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {20,  20,  20,  20,  20,  20,  20,  20}},
	      {{0,   0,   0,  50,  50,   0,   0,   0},
		      {0,   0,  20,  30,  30,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0}},
	      {{0,  20,  50,  30,  50,   0, 100,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0},
		      {0,   0,   0,   0,   0,   0,   0,   0}}};
	for(i = 0; i < 8; i++) {
		q->p[i] = (coin *) malloc (sizeof(coin) * 8);
	}
	fdr = open("coins.txt", O_RDONLY, S_IRWXU);
	if(fdr == -1) {
		printf("Open failed\n");
		exit(1);
	}
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			read(fdr, &a.name[0], 1);
			read(fdr, &a.name[1], 1);
			read(fdr, &a.color, sizeof(int));
			read(fdr, &a.status, sizeof(int));
			q->p[i][j] = a;
		}
	}
	q->enable = DISABLE;
	close(fdr);
	q->state = WHITE;
	//printstate(stdscr, q);
	//getch();
	initlist(q);
	initstack(&q->s);
	initstack(&q->r);
	for(i = 0; i < 12; i++) {
		for(j = 0; j < 8; j++) {
			for(k = 0; k < 8; k++) {
				q->pieceeval[i][j][k] = pevals[i][j][k];
			}
		}
	}
}
void display1(WINDOW *win) {
	int x, y, i;
	attroff(A_BLINK);
	curs_set(0);
	init_pair(1, COLOR_WHITE, COLOR_RED);
	wbkgd(win, COLOR_PAIR(1));
	wrefresh(win);
	for(i = 0; i < 300000000; i++) {
		i = i + 1;
	}
	wmove(win, LINES/2 - 4, COLS/2 - 3);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	waddstr(win, "CHESS");
	wrefresh(win);
	attroff(COLOR_PAIR(3));
	getyx(win, y, x);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(2));
	wmove(win, y + 3, COLS/2 - 8);
	for(i = 0; i < 300000000; i++) {
		i = i + 1;
	}
	waddstr(win, "Use your brain!");
	wrefresh(win);
	for(i = 0; i < 200000000; i++) {
		i = i + 1;
	}
	// getch();//For delay
}
int display2(WINDOW *win) {
	int x, y, n = -1;
	wclear(win);//Clear screen
	init_pair(1, COLOR_WHITE, COLOR_RED);
	wbkgd(win, COLOR_PAIR(1));
	attron(A_BOLD);
	mvwaddstr(win, LINES/4, COLS/2 - 4, "CHESS");
	attroff(A_BOLD);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(2));
	getyx(win, y, x);
	mvwprintw(win, y + 4, COLS/2 - 12, "1. Player vs Player");
	mvwprintw(win, y + 6, COLS/2 - 12, "2. Computer vs Player");
	mvwprintw(win, y + 8, COLS/2 - 12, "3. Player vs Computer");
	mvwprintw(win, y + 10, COLS/2 - 12, "4. HELP");
	mvwprintw(win, y + 12, COLS/2 - 12, "5. About");
	mvwprintw(win, y + 14, COLS/2 - 12, "6. Exit");
	curs_set(1);
	echo();
	while(n == -1) {
		mvwprintw(win, y + 17, COLS/2 - 12, "Enter your command : ");
		wrefresh(win);
		scanw("%d", &n);
		wrefresh(win);
		// wdelch(win);
		if(n > 0 && n < 7) {
			return n;
		}
		else {
			mvwprintw(win, y + 16, COLS/2 - 12, "Please enter a valid choice");
			display2(win);
		}
	}
	sleep(1);
	return n;
}
void display(WINDOW *win, chess *q) {
	clear();
	curs_set(0);
	int endx, endy, i, j, startx, starty, width, height, n, count, x, prev;
	startx = 4;
	starty = 3;
	height = 4;
	width = 11;
	n = 8;
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	wbkgd(win, COLOR_PAIR(1));
	//wrefresh(win);
	attron(COLOR_PAIR(1));
	endx = startx + 8 * width;
	endy = starty + 8 * height;
	for(i = starty; i <= endy; i += height) {//drawing all horizontal lines
		for(j = startx; j <= endx; j++) {
			mvwaddch(win, i, j, ACS_HLINE);
		}
	}
	//wrefresh(win);
	for(i = startx; i <= endx; i += width) {//drawing all vertical lines
		for(j = starty; j <= endy; j++) {
			mvwaddch(win, j, i, ACS_VLINE);
		}
	}
	//wrefresh(win);
	mvwaddch(win, starty, startx, ACS_ULCORNER);
	mvwaddch(win, endy, startx, ACS_LLCORNER);
	mvwaddch(win, starty, endx, ACS_URCORNER);
	mvwaddch(win, endy, endx, ACS_LRCORNER);
	attron(COLOR_PAIR(6));
	mvwaddch(win, endy + 2, startx + width / 2, 'a');
	attroff(COLOR_PAIR(6));
	for(i = startx + width; i < endx; i += width) {
		mvwaddch(win, starty, i, ACS_TTEE);
		attron(COLOR_PAIR(6));
		mvwaddch(win, endy + 2, i + width / 2, (i - startx - width) / width + 98);
		attroff(COLOR_PAIR(6));
		mvwaddch(win, endy, i, ACS_BTEE);
	}
	//wrefresh(win);
	attron(COLOR_PAIR(6));
	mvwaddch(win, starty + height / 2, startx - 2, '8');
	for(i = starty + height; i < endy; i += height) {
		attron(COLOR_PAIR(6));
		mvwaddch(win, i + height / 2, startx - 2, '7' - (i - starty - height) / height );
		attroff(COLOR_PAIR(6));
		mvwaddch(win, i, startx, ACS_LTEE);
		mvwaddch(win, i, endx, ACS_RTEE);
	}
	attron(COLOR_PAIR(6));
	mvwaddstr(win, starty - 1, (endx - startx) / 2 + 2, "BLACK");
	mvwaddstr(win, endy + 3, (endx - startx) / 2 + 2, "WHITE");
	attroff(COLOR_PAIR(6));
	for(i = startx + width; i < endx; i += width) {
		for(j = starty + height; j < endy; j += height) {
			mvwaddch(win, j, i, ACS_PLUS);
		}
	}
	//wrefresh(win);

	//Done drawing the board
	//Now coloring the board
	//set only background color
	init_pair(2, COLOR_GREEN, COLOR_WHITE);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	init_pair(5, COLOR_RED, COLOR_GREEN);
	init_pair(6, COLOR_RED, COLOR_WHITE);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	x = 1;
	for(j = starty + 1; j < endy; j++) {
		if((j - starty) % height != 0) {
			count = 1;
			for(i = startx + 1; i < endx; i++) {
				if((i - startx) % width != 0) {
					if(count < width) {
						//Color white
						if(x == 1) {
							attron(COLOR_PAIR(2));
							mvwaddch(win, j, i, ' ');
							attroff(COLOR_PAIR(2));
							wrefresh(win);
						}
						else {
							attron(COLOR_PAIR(3));
							mvwaddch(win, j, i, ' ');
							attroff(COLOR_PAIR(3));

						}
					}
					else if(count > width - 1) {
						if(x == 1) {
							attron(COLOR_PAIR(3));
							mvwaddch(win, j, i, ' ');
							attroff(COLOR_PAIR(3));
						}
						else {
							attron(COLOR_PAIR(2));
							mvwaddch(win, j, i, ' ');
							attroff(COLOR_PAIR(2));
						}
					}
					count++;
				}
				else {
					count++;
					if(count > 2 * width) {
						count = 1;
					}
				}
			}
		}
		else {
			if(x == 0) {
				x = 1;
			}
			else {
				x = 0;
			}
		}
	}
	//wrefresh(win);

	//Now put coins in the rows
	//You will get the coordinates just you have to arrange them to fit in the center
	for(i = starty; i < endy; i = i + height) {
		for(j = startx; j < endx; j = j + width) {
			if(((j - startx) / width  + (i - starty) / height) % 2 == 0) {
				if(q->p[(i - starty) / height][(j - startx) / width].name[0] == 'W') {
					attron(COLOR_PAIR(6));
					x = 6;
				}
				else {
					attron(COLOR_PAIR(8));
					x = 8;
				}
			}
			else {
				if(q->p[(i - starty) / height][(j - startx) / width].name[0] == 'W') {
					attron(COLOR_PAIR(5));
					x = 5;
				}
				else {
					attron(COLOR_PAIR(7));
					x = 7;
				}
			}
			printcoinw(win, i + height / 2 , j + width / 2, q->p[(i - starty) / height][(j - startx) / width].name);
			attroff(COLOR_PAIR(x));
		}
	}
	mvprintw(16, 110, "Description");
	mvprintw(16, 122, ":");
	wrefresh(win);
}
void printcoinw(WINDOW *win, int y, int x, char *str) {
	int i;
	setlocale(LC_CTYPE, "");
	static wchar_t ch[] = {0x2656, 0x2658, 0x2657, 0x2655, 0x2654, 0x2654, 0x2659, 0x265C, 0x265E, 0x265D, 0x265B, 0x265A, 0x265F, 0x2660};
	if(str[0] == 'W') {
		i = 7;
	}
	else {
		i = 7;
	}
	switch(str[1]) {
		case 'R':
			mvwprintw(win, y, x, "%C", ch[i + 0]);
			break;
		case 'N':
			mvwprintw(win, y, x , "%C", ch[i + 1]);
			break;
		case 'B':
			mvwprintw(win, y, x , "%C", ch[i + 2]);
			break;
		case 'Q':
			mvwprintw(win, y, x , "%C", ch[i + 3]);
			break;
		case 'K':
			mvwprintw(win, y, x , "%C", ch[i + 4]);
			break;
		case 'P':
			mvwprintw(win, y, x , "%C", ch[i + 5]);
	}
}
