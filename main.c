
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

/*This file contains the main() function.
 */ 
#include <ncurses.h>
#include "newchess.h"
int main() {
	int n = 1;
	setlocale(LC_CTYPE, "");
	initscr();//Initialize the screen
	start_color();
	cbreak();
	display1(stdscr);
	while(1) {
		n = display2(stdscr);
		switch(n) {
			case 1:
				n = p_vs_p_mode(stdscr);
				break;
			case 2:
				n = comp_vs_p_mode(stdscr, n);//Player white and computer black
				break;
			case 3:
				n = comp_vs_p_mode(stdscr, n);//Player black and computer white
				break;
			case 4: case 5:
				if(n == 4) {
					n = display_help_about(stdscr, "help");
				}
				else {
					n = display_help_about(stdscr, "about");      
				}
				break;
			case 6:
				break;
			default:
				printf("Please enter a valid number\n");
		}
		if(n == 6) {
			break;
		}
	}
	endwin();
	return 0;
}
