
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

/*This file is used for writing conis.txt
*/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
typedef struct coin {
	char name[2];
	int color;
	int status;
}coin;
enum en{WHITE = 1, BLACK = 2, NOCOLOR = 3, ALIVE = 4, NOSTATUS = 5};
int main(int argc, char *argv[]) {
	int fdw, i;
	coin a;
	fdw = open(argv[1], O_WRONLY | O_CREAT, S_IRWXU);
	if(fdw == -1) {
		printf("Open failed\n");
		return 1;
	}
	for(i = 0; i < 64; i++) {
		if(((i < 8) && (a.color = BLACK) && (a.status = ALIVE)) || ((i > 55) && (a.color = WHITE) && (a.status = ALIVE))) {
			if(a.color == WHITE) {
				a.name[0] = 'W';
			}
			else {
				a.name[0] = 'B';
			}
			switch((i%8)) {
				case 0: case 7:
					a.name[1] = 'R';
					break;
				case 1: case 6:
					a.name[1] = 'N';
					break;
				case 2: case 5:
					a.name[1] = 'B';
					break;
				case 3:
					a.name[1] = 'Q';
					break;
				case 4:
					a.name[1] = 'K';
					break;
			}
		}
		else if(((i < 16) && (a.name[1] = 'P')) || ((i > 47) && (a.name[1] = 'P') && (a.color = WHITE) && (a.status = ALIVE) && (a.name[0] = 'W')));//Already color is Black and so
		else {
			a.name[0] = a.name[1] = '_';
			a.color = NOCOLOR;
			a.status = NOSTATUS;
		}
		write(fdw, &a.name[0], 1);
		write(fdw, &a.name[1], 1);
		write(fdw, &a.color, sizeof(int));
		write(fdw, &a.status, sizeof(int));
	}
	close(fdw);
	return 0;
}
