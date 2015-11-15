
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

/*This file includes the code to play the computer move but presently it has some errors to be fixed
*/
#include "newchess.h"
void inittree(tree **t) {
	*t = (tree *) malloc(sizeof(tree));
}
void insertnodes(tree **t, moveslist *l, int depth) {
	//printw("Entered insertnodes");
	//getch();
	int i, j;
	tree *p;
	moves *r;
	p = *t;
	r = l->tail;
	p->numchildren = l->count;
	if(depth == 0) {
		p->parent = NULL;
	}
	if(l->count > 0) {
		p->children = (tree **) malloc (sizeof(tree) * l->count);
		if(p->children == 0) {
			printw("Malloc of children failed");
			getch();
			return;
		}
		for(i = 0; i < l->count; i++) {
			p->children[i] = (tree *) malloc(sizeof(tree));
			p->children[i]->parent = p;
			//*(p->children[i]->children) = NULL;
			if(depth % 2 == 0) {
				p->score = INT_MIN;
			}
			else {
				p->score = INT_MAX;
			}
			for(j = 0; j < 4; j++) {
				p->children[i]->loc[j] = r->prloc[j];
				p->children[i]->loc[j + 4] = r->locinput[j];
			}
			r = r->previous;
			if(r == NULL) {
				break;
			}
		}
	}
	//printw("Returned from insertnodes");
}
void compmove(chess *q) {
	//printw("Entered compmove");
	//getch();
	int score, i;
	q->depth = 0;
	score = build(q, &q->t, 0);
	for(i = 0; i < q->t->numchildren; i++) {
		if(q->t->children[i]->score == score) {
			break;
		}
	}
	display(stdscr, q);
	getch();
	push(q, &q->s, q->t->children[i]->loc, &q->t->children[i]->loc[4]);
	move1(q, q->t->children[i]->loc, &q->t->children[i]->loc[4], "no");
	free(q->t);
	printw("Returned from compmove");
	getch();
}
int build(chess *q, tree **t, int start) {
	//printw("Entered build");
	//getch();
	tree *p;
	int i, k;
	if(q->depth >= DEPTH) {
		//printw("Ent if q->depth");
		//getch();
		push(q, &q->s, p->loc, &p->loc[4]);
		move1(q, p->loc, &p->loc[4], "exp");
		q->depth--;
		k = eval(q);
		undoredo(q, "undowithoutredo");
		return k;
	}
	inittree(t);
	p = *t;
	initmoveslist(p);
	generatemoves(q, p);
	printmlist(p);
	insertnodes(&p, p->ml, q->depth);
	if(start == 0) {
		start = 1;
	}
	else {
		push(q, &q->s, p->loc, &p->loc[4]);
		move1(q, p->loc, &p->loc[4], "exp");
	}
	for(i = 0; i < p->numchildren; i++) {
		q->depth++;
		p->children[i]->score = build(q, &p->children[i], start);
		if((q->depth % 2) == 1) {
			p->score = min(p->score, p->children[i]->score);
		}
		else {
			p->score = max(p->score, p->children[i]->score);
		}
	}
	p->score = -p->score;
	if(p->parent == NULL) {
		return p->score;
	}
	undoredo(q, "undowithoutredo");
	q->depth--;
}
