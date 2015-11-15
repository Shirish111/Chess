
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

/*This file has functions related to list datastructure which is used for storing the locations of all pieces except pawns
 */
#include "newchess.h"
/*List will never be empty*/
void initlist(chess *q) {
	node *p;
	int i, j;
	q->l = (list *)malloc(sizeof(list));
	q->l->head = (node*)malloc(sizeof(node));
	p = q->l->head;
	p->previous = NULL;
	for(i = 0; i < 8; i = i + 7) {
		for(j = 0;j < 8; j++) {
			p->loc[0] = convertp(q->p[i][j].name[1]);
			p->color = q->p[i][j].color;
			p->loc[1] = i;
			p->loc[2] = j;
			p->loc[3] = NOKILL;
			p->moved = NOTMOVED;
			if(j == 7 && i == 7) {
				p->next = NULL;
				break;
			}
			p->next = (node*) malloc (sizeof(node));
			p->next->previous = p;
			p = p->next;
		}
	}
	q->l->tail = p;
	q->l->count = 16;
}
void printlist(chess *q) {
	/* The list is never empty */
	node *p;
	int i;
	p = q->l->head;
	while(p) {
		if(p->color == WHITE) {
			printf("White\n");
		}
		else {
			printf("Black\n");
		}
		convprint(p->loc);
		p = p->next;
	}
}
/* If you want if certain piece is moved or not then pass address of int as argument to search else pass NULL */
int *search(chess *q, int name, int color, int *moved1, int *moved2) {
	node *p;
	int *loc, i = 0, j, count = 0;
	p = q->l->head;
	loc = (int*) malloc (sizeof(int) * 8);
	for(i = 0; i < 8; i++) {
		loc[i] = NOTFOUND;/* Initialize to NOTFOUND */
	}
	i = 0;
	while(p) {
		if((p->color == color) && (p->loc[0] == name)) {
			loc[i++] = p->loc[0];
			loc[i++] = p->loc[1];
			loc[i++] = p->loc[2];
			loc[i++] = p->loc[3];
			if(count == 0) {
				if(moved1 != NULL) {
					*moved1 = p->moved;
				}
			}
			else if(count == 1) {
				if(moved2 != NULL) {
					*moved2 = p->moved;
				}
			}
			count++;
			if(count == 2) {
				break;
			}
		}
		p = p->next;
	}
	return loc;
}
int remov(chess *q, int *loc) {
	node *p;
	int found = 0, i;
	p = q->l->head;
	while(p) {
		if((p->loc[0] == loc[0]) && (p->loc[1] == loc[1]) && (p->loc[2] == loc[2])) {
			if(p == q->l->head) {
				q->l->head->next->previous = NULL;
				q->l->head = q->l->head->next;
				free(p);
			}
			else if(p == q->l->tail) {
				q->l->tail = q->l->tail->previous;
				q->l->tail->next = NULL;
				free(p);
			}
			else {
				p->next->previous = p->previous;
				p->previous->next = p->next;
				free(p);
			}
			p = NULL;
			found = 1;
		}
		else {
			p = p->next;
		}
	}
	if(found != 1) {
		return 1;/* Not found */
	}
	return 0;/* Successful */
}
int update(chess *q, int *prev, int *new) {
	node *p;
	int i;
	p = q->l->head;
	while(p) {
		if((p->loc[0] == prev[0]) && (p->loc[1] == prev[1]) && (p->loc[2] == prev[2])) {
			/*Element found*/
			for(i = 0; i < 4; i++) {
				p->loc[i] = new[i];
			}
			if(p->moved = NOTMOVED) {
				p->moved = MOVED;
			}
			else {
				p->moved += 1;
			}
			break;
		}
		else {
			p = p->next;
		}
	}
	return 0;/* Successful */
}
int append(chess *q, int *loc3, int color) {
	int i;
	node *p;
	p = q->l->tail;
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	tmp->next = NULL;
	for(i = 0; i < 4; i++) {
		tmp->loc[i] = loc3[i];
	}
	tmp->color = color;
	tmp->moved = MOVED;
	p->next = tmp;
	tmp->previous = p;
	q->l->tail = tmp;
	return 0;/* Successful */
}
void unmove(chess *q, int *loc, char *str) {
	node *p;
	int i;
	p = q->l->head;
	while(p) {
		if((p->loc[0] == loc[0]) && (p->loc[1] == loc[1]) && (p->loc[2] == loc[2])) {
			/*Element found*/
			if(strcmp(str, "move") == 0) {
				if(p->moved == NOTMOVED) {
					p->moved = MOVED;
				}
				else if(p->moved == MOVED) {
					p->moved += 1;
				}
				else {
					p->moved += 1;
				}
			}
			else {
				if(p->moved == NOTMOVED);
				else if(p->moved == MOVED) {
					p->moved = NOTMOVED;
				}
				else {
					p->moved -= 1;
				}
				break;
			}
		}
		else {
			p = p->next;
		}
	}
}
