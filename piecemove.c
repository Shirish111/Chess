
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

/*This file contains the following functions
 *piecesmove() which checks if a valid move can be done by any piece (except pawn)
 *piecesearchlist() which is used to fetch the location of the pieces
 *legalpiecemove() function which generates the moves and checks for the validity of the move and if valid it returns * 1
 *addvisited() which is used to store the visited locations
 *visitedf() which is used to check if the location is visited previously
 *pawnsmove() which is used to check if a valid move can be done with any pawn
 *legalpawnmove() which generates the pawn moves and checks for validity of the move
 */
#include "newchess.h"
int piecesmove(chess *q) {
	int *prloc;
	prloc = piecesearchlist(q, NULL);
	do {
		if(prloc) {
			if(legalpiecemove(q, prloc)) {
				return 1;/* valid */
			}
		}
		prloc = (int *)piecesearchlist(q, prloc);
	}
	while(prloc);
	return 0;
}
int *piecesearchlist(chess *q, int *prloc) {
	int start, i;
	if(prloc == NULL) {
		start = KNIGHT;
	}
	else {
		start = prloc[0] + 1;
	}
	for(i = start; i <= KING; i++) {
		prloc = search(q, i, q->state, NULL, NULL);
		if(prloc) {
			return prloc;
		}
	}
	return NULL;
}
int legalpiecemove(chess *q, int *prloc) {
	int *newloc, **visited, i, j, valid, count = 0;//8 * 2 table
	newloc = (int *) malloc (sizeof(int) * 4);
	switch(prloc[0]) {
		case KNIGHT:
			newloc[0] = KNIGHT;
			visited = (int **) malloc (sizeof(int *) * 8);//Has to hold at most 8 pairs
			for(j = 0; j < 2; j++) {
				for(i = 0; i < 8; i++) {
					visited[i] = (int *) malloc (sizeof(int) * 2);
					visited[i][0] = -1;
					visited[i][1] = -1;
				}
				/* generate the moves for knight and move them and check for valid. If yes then return 1 */
				/* Checks for all valid locations and returns 1 if valid */
				for(i = 0; i < 8; i++) {
					if(((prloc[1] + 1 < 8 && prloc[2] + 2 < 8) && ((q->p[prloc[1] + 1][prloc[2] + 2].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2] + 2].status == ALIVE && q->p[prloc[1] + 1][prloc[2] + 2].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2] + 2) && !visitedf(visited, 8, prloc[1] + 1, prloc[2] + 2)) || ((prloc[1] + 1 < 8 && prloc[2] - 2 >= 0) && ((q->p[prloc[1] + 1][prloc[2] - 2].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2] - 2].status == ALIVE && q->p[prloc[1] + 1][prloc[2] - 2].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2] - 2) && !visitedf(visited, 8, prloc[1] + 1, prloc[2] - 2)) || ((prloc[1] - 1 >= 0 && prloc[2] + 2 < 8) &&((q->p[prloc[1] - 1][prloc[2] + 2].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 1][prloc[2] + 2].status == ALIVE && q->p[prloc[1] - 1][prloc[2] + 2].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2] + 2) && !visitedf(visited, 8, prloc[1] - 1, prloc[2] + 2)) || ((prloc[1] - 1 >= 0 && prloc[2] - 2 >= 0) && ((q->p[prloc[1] - 1][prloc[2] - 2].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 1][prloc[2] - 2].status == ALIVE && q->p[prloc[1] - 1][prloc[2] - 2].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2] - 2) && !visitedf(visited, 8, prloc[1] - 1, prloc[2] - 2)) || ((prloc[1] + 2 < 8 && prloc[2] + 1 < 8) && ((q->p[prloc[1] + 2][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 2][prloc[2] + 1].status == ALIVE && q->p[prloc[1] + 2][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 2, newloc[2] = prloc[2] + 1) && !visitedf(visited, 8, prloc[1] + 2, prloc[2] + 1)) || ((prloc[1] + 2 < 8 && prloc[2] - 1 >= 0) && ((q->p[prloc[1] + 2][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 2][prloc[2] - 1].status == ALIVE && q->p[prloc[1] + 2][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 2, newloc[2] = prloc[2] - 1) && !visitedf(visited, 8, prloc[1] + 2, prloc[2] - 1)) || ((prloc[1] - 2 >= 0 && prloc[2] + 1 < 8) && ((q->p[prloc[1] - 2][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 2][prloc[2] + 1].status == ALIVE && q->p[prloc[1] - 2][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 2, newloc[2] = prloc[2] + 1) && !visitedf(visited, 8, prloc[1] - 2, prloc[2] + 1)) || ((prloc[1] - 2 >= 0 && prloc[2] - 1 >= 0) && ((q->p[prloc[1] - 2][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 2][prloc[2] - 1].status == ALIVE && q->p[prloc[1] - 2][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 2, newloc[2] = prloc[2] - 1) && !visitedf(visited, 8, prloc[1] - 2, prloc[2] - 1))) {
						push(q, &q->s, prloc, newloc);
						move1(q, prloc, newloc, "exp");
						valid = verifycheck(q);
						changestate(q);
						undoredo(q, "undowithoutredo");
						if(valid == NOCHECK) {
							free(visited);
							return 1;
						}
						addvisited(visited, 8, newloc[1], newloc[2]);
					}
					else {
						break;
					}
				}
				count++;
				if(count == 1) {
					if(prloc[4] == NOTFOUND) {
						free(visited);
						return 0;
					}
				}
			}
			free(visited);
			return 0;
			break;
		case BISHOP:
			visited = (int **) malloc (sizeof(int *) * 4);//Has to hold at most 8 pairs
			newloc[0] = BISHOP;
			for(j = 0; j < 2; j++) {
				for(i = 0; i < 4; i++) {
					visited[i] = (int *) malloc (sizeof(int) * 2);
					visited[i][0] = -1;
					visited[i][1] = -1;
				}
				for(i = 0; i < 4; i++) {
					/* See if you can put the piece in the four squares */
					if(((prloc[1] + 1 < 8 && prloc[2] + 1 < 8) && ((q->p[prloc[1] + 1][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2] + 1].status == ALIVE && q->p[prloc[1] + 1][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2] + 1) && !visitedf(visited, 4, prloc[1] + 1, prloc[2] + 1)) || ((prloc[1] + 1 < 8 && prloc[2] - 1 >= 0) && ((q->p[prloc[1] + 1][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2] - 1].status == ALIVE && q->p[prloc[1] + 1][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2] - 1) && !visitedf(visited, 4, prloc[1] + 1, prloc[2] - 1)) || ((prloc[1] - 1 >= 0 && prloc[2] + 1 < 8) && ((q->p[prloc[1] - 1][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 1][prloc[2] + 1].status == ALIVE && q->p[prloc[1] - 1][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2] + 1) && !visitedf(visited, 4, prloc[1] - 1, prloc[2] + 1)) || ((prloc[1] - 1 >= 0 && prloc[2] - 1 >= 0) && ((q->p[prloc[1] - 1][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 1][prloc[2] - 1].status == ALIVE && q->p[prloc[1] - 1][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2] - 1) && !visitedf(visited, 4, prloc[1] - 1, prloc[2] - 1))) {
						push(q, &q->s, prloc, newloc);
						move1(q, prloc, newloc, "exp");
						valid = verifycheck(q);
						changestate(q);
						undoredo(q, "undowithoutredo");
						if(valid == NOCHECK) {
							free(visited);
							return 1;
						}
						addvisited(visited, 4, newloc[1], newloc[2]);
					}
					else {
						break;
					}
				}
				count++;
				if(count == 1) {
					if(prloc[4] == NOTFOUND) {
						free(visited);
						return 0;
					}
				}
			}

			free(visited);
			return 0;
			break;
		case ROOK:
			visited = (int **) malloc (sizeof(int *) * 4);//Has to hold at most 8 pairs
			newloc[0] = ROOK;
			for(j = 0; j < 2; j++) {
				for(i = 0; i < 4; i++) {
					visited[i] = (int *) malloc (sizeof(int) * 2);
					visited[i][0] = -1;
					visited[i][1] = -1;
				}
				for(i = 0; i < 4; i++) {
					if(((prloc[1] + 1 < 8) && ((q->p[prloc[1] + 1][prloc[2]].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2]].status == ALIVE && q->p[prloc[1] + 1][prloc[2]].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2]) && !visitedf(visited, 4, prloc[1] + 1, prloc[2])) || ((prloc[1] - 1 >= 0) && ((q->p[prloc[1] - 1][prloc[2]].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1]- 1][prloc[2]].status == ALIVE && q->p[prloc[1] - 1][prloc[2]].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2]) && !visitedf(visited, 4, prloc[1] - 1, prloc[2])) || ((prloc[2] + 1 < 8) && ((q->p[prloc[1]][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1]][prloc[2] + 1].status == ALIVE && q->p[prloc[1]][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1], newloc[2] = prloc[2] + 1) && !visitedf(visited, 4, prloc[1], prloc[2] + 1)) || ((prloc[2] - 1 >= 0) && ((q->p[prloc[1]][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1]][prloc[2] - 1].status == ALIVE && q->p[prloc[1]][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1], newloc[2] = prloc[2] - 1) && !visitedf(visited, 4, prloc[1], prloc[2] - 1))) {
						push(q, &q->s, prloc, newloc);
						move1(q, prloc, newloc, "exp");
						valid = verifycheck(q);
						changestate(q);
						undoredo(q, "undowithoutredo");
						if(valid == NOCHECK) {
							free(visited);
							return 1;
						}
						addvisited(visited, 4, newloc[1], newloc[2]);
					}
					else {
						break;
					}
				}
				count++;
				if(count == 1) {
					if(prloc[4] == NOTFOUND) {
						free(visited);
						return 0;
					}
				}
			}
			free(visited);
			return 0;
			break;
		case QUEEN: case KING:
			visited = (int **) malloc (sizeof(int *) * 8);//Has to hold at most 8 pairs
			newloc[0] = prloc[0];
			for(i = 0; i < 8; i++) {
				visited[i] = (int *) malloc (sizeof(int) * 2);
				visited[i][0] = -1;
				visited[i][1] = -1;
			}
			for(i = 0; i < 8; i++) {
				if(((prloc[1] + 1 < 8) && ((q->p[prloc[1] + 1][prloc[2]].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2]].status == ALIVE && q->p[prloc[1] + 1][prloc[2]].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2]) && !visitedf(visited, 4, prloc[1] + 1, prloc[2])) || ((prloc[1] - 1 >= 0) && ((q->p[prloc[1] - 1][prloc[2]].status == NOSTATUS && (newloc[3] = NOKILL))) || (q->p[prloc[1]- 1][prloc[2]].status == ALIVE && q->p[prloc[1] - 1][prloc[2]].color == q->prevstate && (newloc[3] = KILL)) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2]) && !visitedf(visited, 4, prloc[1] - 1, prloc[2])) || ((prloc[2] + 1 < 8) && ((q->p[prloc[1]][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1]][prloc[2] + 1].status == ALIVE && q->p[prloc[1]][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1], newloc[2] = prloc[2] + 1) && !visitedf(visited, 4, prloc[1], prloc[2] + 1)) || ((prloc[2] - 1 >= 0) && ((q->p[prloc[1]][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1]][prloc[2] - 1].status == ALIVE && q->p[prloc[1]][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1], newloc[2] = prloc[2] - 1) && !visitedf(visited, 4, prloc[1], prloc[2] - 1)) || ((prloc[1] + 1 < 8 && prloc[2] + 1 < 8) && ((q->p[prloc[1] + 1][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2] + 1].status == ALIVE && q->p[prloc[1] + 1][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2] + 1) && !visitedf(visited, 4, prloc[1] + 1, prloc[2] + 1)) || ((prloc[1] + 1 < 8 && prloc[2] - 1 >= 0) && ((q->p[prloc[1] + 1][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] + 1][prloc[2] - 1].status == ALIVE && q->p[prloc[1] + 1][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] + 1, newloc[2] = prloc[2] - 1) && !visitedf(visited, 4, prloc[1] + 1, prloc[2] - 1)) || ((prloc[1] - 1 >= 0 && prloc[2] + 1 < 8) && ((q->p[prloc[1] - 1][prloc[2] + 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 1][prloc[2] + 1].status == ALIVE && q->p[prloc[1] - 1][prloc[2] + 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2] + 1) && !visitedf(visited, 4, prloc[1] - 1, prloc[2] + 1)) || ((prloc[1] - 1 >= 0 && prloc[2] - 1 >= 0) && ((q->p[prloc[1] - 1][prloc[2] - 1].status == NOSTATUS && (newloc[3] = NOKILL)) || (q->p[prloc[1] - 1][prloc[2] - 1].status == ALIVE && q->p[prloc[1] - 1][prloc[2] - 1].color == q->prevstate && (newloc[3] = KILL))) && (newloc[1] = prloc[1] - 1, newloc[2] = prloc[2] - 1) && !visitedf(visited, 4, prloc[1] - 1, prloc[2] - 1))) {
					push(q, &q->s, prloc, newloc);
					move1(q, prloc, newloc, "exp");
					valid = verifycheck(q);
					changestate(q);
					undoredo(q, "undowithoutredo");
					if(valid == NOCHECK) {
						free(visited);
						return 1;
					}
					addvisited(visited, 8, newloc[1], newloc[2]);
				}
				else {
					break;
				}
			}
			free(visited);
			return 0;
			break;
	}
}
void addvisited(int **visited, int n, int n1, int n2) {
	int i;
	for(i = 0; i < n; i++) {
		if(visited[i][0] == -1) {
			visited[i][0] = n1;
			visited[i][0] = n2;
			break;
		}
	}
}
int visitedf(int **visited, int n, int n1, int n2) {
	/* Search in the table and find if the pair exists */
	int i;
	for(i = 0; i < n; i++) {
		if(visited[i][0] == n1 && visited[i][1] == n2) {
			return 1;
		}
	}
	return 0;
}
int pawnsmove(chess *q) {
	int i, j;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(q->p[i][j].name[1] == 'P' && q->p[i][j].color == q->state) {
				if(legalpawnmove(q, i, j)) {
					return 1;
				}
			}
		}
	}
	return 0;
}
int legalpawnmove(chess *q,int i,int j) {
	int *prloc, *locinput, valid, count, k;
	prloc = (int *) malloc (sizeof(int) * 4);
	locinput = (int *) malloc (sizeof(int) * 4);
	prloc[0] = locinput[0] = PAWN;
	if(q->state == WHITE) {
		count = -1;
	}
	else {
		count = 1;
	}
	/* 3 possibilities to be checked */
	if(i + count >= 0 && i + count < 8) {
		locinput[1] = i + count;
		locinput[2] = j;
		locinput[3] = NOKILL;
		if(correctness(q, locinput)) {
			prloc = pawnsearch(q, locinput);
			if(prloc) {
				push(q, &q->s, prloc, locinput);
				move1(q, prloc, locinput, "exp");
				valid = verifycheck(q);
				changestate(q);
				undoredo(q, "undowithoutredo");
				if(valid == NOCHECK) {
					free(prloc);
					free(locinput);
					return 1;
				}
			}
		}
		if(j - 1 >= 0) {
			locinput[2] = j - 1;
			locinput[3] = KILL;
			if(correctness(q, locinput)) {
				prloc = pawnsearch(q, locinput);
				if(prloc) {
					push(q, &q->s, prloc, locinput);
					move1(q, prloc, locinput, "exp");
					valid = verifycheck(q);
					changestate(q);
					undoredo(q, "undowithoutredo");
					if(valid == NOCHECK) {
						free(prloc);
						free(locinput);
						return 1;
					}
				}
			}
		}
		if(j + 1 < 8) {
			locinput[2] = j + 1;
			locinput[3] = KILL;
			if(correctness(q, locinput)) {
				prloc = pawnsearch(q, locinput);
				if(prloc[0] == CONF) {
					prloc[0] = PAWN;
					prloc[3] = KILL;
					prloc[1] = i;
					for(k = 0; k < 2; k += 2) {
						prloc[2] = j + k;
						push(q, &q->s, prloc, locinput);
						move1(q, prloc, locinput, "exp");
						valid = verifycheck(q);
						changestate(q);
						undoredo(q, "undowithoutredo");
						if(valid == NOCHECK) {
							free(prloc);
							free(locinput);
							return 1;
						}
					}
				}
				else if(prloc[0] != NOTFOUND) {
					push(q, &q->s, prloc, locinput);
					move1(q, prloc, locinput, "exp");
					valid = verifycheck(q);
					changestate(q);
					undoredo(q, "undowithoutredo");
					if(valid == NOCHECK) {
						free(prloc);
						free(locinput);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
