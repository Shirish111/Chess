
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

/*This file includes the function writetofile() which is used to write moves being played during the game into a file
 */
#include "newchess.h"
void writetofile(chess *q, char *s) {
	static int fdw;
	static int i = 1;
	FILE *fp;
	int j = 0, count = 0;
	char c = '\t', cb[6];
	if(i == 1) {
		fp = fopen("MovesList1.txt", "w");
		if(fp == NULL) {
			printf("Error opening the file\n");
			exit(1);
		}
		fclose(fp);
		fdw = open("MovesList1.txt", O_WRONLY | O_CREAT | O_RDONLY, S_IRWXU);
		if(fdw == -1) {
			printf("Error opening the file MovesList.txt\n");
			exit(1);
		}
	}
	if(strcmp(s, "Check") == 0) {
		c = '+';
		lseek(fdw, -1, SEEK_CUR);
		read(fdw, &c, 1);
		if(c == '\n') {
			c = '+';
			lseek(fdw, -1, SEEK_CUR);
			write(fdw, &c, 1);
			c = '\n';
		}
		else if(c == '\t') {
			c = '+';
			lseek(fdw, -1, SEEK_CUR);
			write(fdw, &c, 1);
			c = ' ';
		}
		write(fdw, &c, 1);
		return;
	}
	else if(strcmp(s, "checkmate") == 0) {
		if(q->state == WHITE) {
			strcpy(cb,"0 - 1");
		}
		else {
			strcpy(cb,"1 - 0");
		}
		for(i = 0; i < 6; i++) {
			write(fdw, &cb[i], 1);
		}
	}
	else if(strcmp(s, "Done") == 0) {
		i = 1;
	}
	else if(strcmp(s, "back") == 0) {
		while(1) {
			lseek(fdw, -1, SEEK_CUR);
			read(fdw, &c, 1);
			if(c == '\t') {
				count++;
			}
			lseek(fdw, -1, SEEK_CUR);
			if(count == 2) {
				break;
			}
		}
	}
	c = '.';
	write(fdw, &i, sizeof(int));
	write(fdw, &c, 1);
	c = ' ';
	write(fdw, &c, 1);
	while(s[j++] != '\0') {
		write(fdw, &s[j - 1], 1);
	}
	write(fdw, &s[j-1], 1);
	if(i % 2 == 0) {
		c = '\n';
		write(fdw, &c, 1);
	}
	else {
		c = '\t';
		write(fdw, &c, 1);
	}
	i++;
}
