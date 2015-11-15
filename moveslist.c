
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

#include "newchess.h"
void initmoveslist(tree *t) {
	t->ml = (moveslist *) malloc(sizeof(moveslist));
	t->ml->head = NULL;
	t->ml->tail = NULL;
	t->ml->count = 0;
}
void addtolist(tree *t, int *prloc, int *locinput) {
	moves *p;
	int i;
	if(t->ml->head == NULL) {
		t->ml->head = (moves *) malloc(sizeof(moves));
		t->ml->tail = t->ml->head;
		t->ml->tail->previous = NULL;
	}
	else {
		t->ml->tail->next = (moves *) malloc(sizeof(moves));
		t->ml->tail->next->previous = t->ml->tail;
		t->ml->tail = t->ml->tail->next;
	}
	p = t->ml->tail;
	for(i = 0; i < 4; i++) {
		p->prloc[i] = prloc[i];
		p->locinput[i] = locinput[i];
	}
	(t->ml->count)++;
	p->next = NULL;
}
void printmlist(tree *t) {
	int i;
	moves *p;
	p = t->ml->head;
	while(p) {
		printw("prloc, locinput");
		for(i = 0; i < 4; i++) {
			printw("%d %d", p->prloc[i], p->locinput[i]);
		}
		getch();
		p = p->next;

	}
}
