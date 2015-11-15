
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

/*This file contains all the functions related to stack which is used for undo and redo operations of the game
 */
#include "newchess.h"
void initstack(stack *s) {
	s->head = NULL;
	s->tail = NULL;
	s->count = 0;
}
void push(chess *q, stack *s, int *prloc, int *locinput) {
	stacknode *p;
	int i;

	if(s->head == NULL) {
		s->head = (stacknode *) malloc (sizeof(stacknode));
		s->tail = s->head;
		s->head->previous = NULL;
	}
	else {
		s->tail->next = (stacknode *) malloc (sizeof(stacknode));
		s->tail->next->previous = s->tail;
		s->tail = s->tail->next;
		s->tail->next = NULL;
	}
	p = s->tail;
	p->prloc = (int *)malloc(sizeof(int) * 4);
	p->locinput = (int *)malloc(sizeof(int) * 4);
	for(i = 0; i < 4; i++) {
		p->prloc[i] = prloc[i];
		p->locinput[i] = locinput[i];
	}
	if(locinput[3] == KILL) {
		p->loc3 = (int *)malloc(sizeof(int) * 5);
		p->loc3[0] = convertp(q->p[locinput[1]][locinput[2]].name[1]);
		p->loc3[1] = locinput[1];
		p->loc3[2] = locinput[2];
		p->loc3[3] = NOKILL;
		p->loc3[4] = q->prevstate;/* Color */
	}
	else {
		p->loc3 = NULL;
	}
	s->count++;

}
int *pop(chess *q, stack *s) {
	stacknode *p;
	int *loc, i;
	loc = (int *)malloc(sizeof(int) * 13);
	if(loc == NULL) {
		printw("Malloc failed");
		getch();
		exit(1);
	}
	if(empty(s) == 1) {
		mvprintw(25, 110, "Empty Stack");
		getch();
		changestate(q);
		return NULL;
	}
	p = s->tail;
	for(i = 0; i < 4; i++) {
		loc[i] = p->prloc[i];
		loc[i + 4] = p->locinput[i];
	}
	if(p->loc3) {/* If killed then restoring the piece */
		for(i = 8; i < 13; i++) {
			loc[i] = p->loc3[i-8];
		}
		if(p->loc3[0] != PAWN) {
			append(q, p->loc3, p->loc3[4]);
		}
	}
	if(p->previous) {
		s->tail = p->previous;
		s->tail->next = NULL;
	}
	else {
		s->head = NULL;	
		s->tail = NULL;
	}
	free(p);
	s->count--;
	return loc;
}
int empty(stack *s){
	if(s->head) {
		return 0;
	}
	return 1;
}
void printstack(stack *s) {
	stacknode *p;
	int i, count;
	p = s->head;
	while(p) {
		printw("prloc\tlocinput");
		for(i = 0; i < 4; i++) {
			printw("%d\t%d", p->prloc[i], p->locinput[i]);
		}
		if(p->loc3) {
			printw("loc3");
			for(i = 0; i < 5; i++) {
				printw("%d\t", p->loc3[i]);
			}
		}
		p = p->next;
	}
}
void freeredo(chess *q, stack *s) {
	int a;
	a = s->count;
	while(s->count != 0) {
		pop(q, s);
	}
}
