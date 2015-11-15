
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
/*This file has some errors to be fixed
*It is used to generate moves for the computer to play
*/
#include "newchess.h"
void generatemoves(chess *q, tree *t) {
	int *loc, *newloc, *prloc, p, valid, n1, n2, i, j, k, chcounter = 0;
	prloc = (int *) malloc (sizeof(int) * 4);
	newloc = (int *) malloc (sizeof(int) * 4);
	p = KNIGHT;
	while(1) {
		loc = search(q, p, q->comp, NULL, NULL);
		if(loc == NULL) {
			break;
		}
		newloc[0] = loc[0];
		switch(loc[0]) {
			case KNIGHT:
				printw("Entered case KnIght");
				getch();
				//      newloc[0] = loc[0];
				for(k = 0; k < 2; k++) {
					for(i = 0; i < 8; i++) {
						switch(i) {
							case 0:
								n1 = 2;
								n2 = 1;
								break;
							case 1:
								n1 = 2;
								n2 = -1;
								break;
							case 2:
								n1 = -2;
								n2 = 1;
								break;
							case 3:
								n1 = -2;
								n2 = -1;
								break;
							case 4:
								n1 = 1;
								n2 = 2;
								break;
							case 5:
								n1 = 1;
								n2 = -2;
								break;
							case 6:
								n1 = -1;
								n2 = 2;
								break;
							case 7:
								n1 = -1;
								n2 = -2;
								break;
						}
						if(loc[1] +  n1 >= 0 && loc[1] +  n1 < 8 && loc[2] + n2 >= 0 && loc[2] + n2 < 8) {
							newloc[1] = loc[1] + n1;
							newloc[2] = loc[2] + n2;
							if(q->p[newloc[1]][newloc[2]].status == ALIVE && q->p[newloc[1]][newloc[2]].color == q->comp) {

							}
							else {
								if(q->p[newloc[1]][newloc[2]].status == ALIVE && q->p[newloc[1]][newloc[2]].color != q->comp) {
									newloc[3] = KILL;
								}
								else {
									newloc[3] = NOKILL;
								}
								push(q, &q->s, loc, newloc);
								move1(q, loc, newloc, "exp");
								if(chcounter == 0) {
									valid = verifycheck(q);
									changestate(q);
									if(valid == CHECK) {
										i = 8;
										break;
									}
									else {
										chcounter = 1;
									}
								}
								undoredo(q, "undowithoutredo");
								addtolist(t, loc, newloc);
							}

						}
						if(i == 7) {
							if(loc[4] == NOTFOUND) {
								k = 3;
							}
							else {
								loc[1] = loc[5];
								loc[2] = loc[6];
							}
						}
					}
				}
				break;
			case BISHOP:case ROOK :
				printw("Entered case b or R");
				getch();
				newloc[0] = loc[0];
				for(k = 0; k < 2; k++) {
					for(i = 0; i < 4; i++) {/* Four cross directions */
						if(loc[0] == BISHOP) {
							switch(i) {
								case 0:
									n1 = -1;
									n2 = -1;
									break;
								case 1:
									n1 = -1;
									n2 = 1;
									break;
								case 2:
									n1 = 1;
									n2 = -1;
									break;
								case 3:
									n1 = 1;
									n2 = 1;
									break;
							}
						}
						else {
							switch(i) {
								case 0:
									n1 = -1;
									n2 = 0;
									break;
								case 1:
									n1 = 1;
									n2 = 0;
									break;
								case 2:
									n1 = 0;
									n2 = -1;
									break;
								case 3:
									n1 = 0;
									n2 = 1;
									break;
							}
						}
						for(j = 0; j < 7; j++) {
							if(loc[1] + j * n1 >= 0 && loc[1] + j * n1 < 8 && loc[2] + j * n2 >= 0 && loc[2] + j * n2 < 8) {
								newloc[1] = loc[1] + j * n1;
								newloc[2] = loc[2] + j * n2;
								if(q->p[newloc[1]][newloc[2]].status == ALIVE && q->p[newloc[1]][newloc[2]].color == q->comp) {
									break;
								}
								else if(q->p[newloc[1]][newloc[2]].status == ALIVE && q->p[newloc[1]][newloc[2]].color != q->comp) {
									newloc[3] = KILL;
								}
								else {
									newloc[3] = NOKILL;
								}
								push(q, &q->s, loc, newloc);
								move1(q, loc, newloc, "exp");
								if(chcounter == 0) {
									valid = verifycheck(q);
									changestate(q);
									if(valid == CHECK) {
										i = 4;
										break;
									}
									else {
										chcounter = 1;
									}
								}
								undoredo(q, "undowithoutredo");
								addtolist(t, loc, newloc);
							}
						}
					}
					if(loc[4] == NOTFOUND) {
						break;
					}
					else {
						loc = &loc[4];
					}
				}
				break;
			case QUEEN:case KING:
				printw("Entered case King or Q");
				getch();
				for(i = 0; i < 8; i++) {/* Eight directions */
					switch(i) {
						case 0:
							n1 = -1;
							n2 = -1;
							break;
						case 1:
							n1 = -1;
							n2 = 1;
							break;
						case 2:
							n1 = 1;
							n2 = -1;
							break;
						case 3:
							n1 = 1;
							n2 = 1;
							break;
						case 4:
							n1 = -1;
							n2 = 0;
							break;
						case 5:
							n1 = 1;
							n2 = 0;
							break;
						case 6:
							n1 = 0;
							n2 = -1;
							break;
						case 7:
							n1 = 0;
							n2 = 1;
							break;
					}
					for(j = 0; j < 7; j++) {
						if(loc[1] + j * n1 >= 0 && loc[1] + j * n1 < 8 && loc[2] + j * n2 >= 0 && loc[2] + j * n2 < 8) {
							newloc[1] = loc[1] + j * n1;
							newloc[2] = loc[2] + j * n2;
							if(q->p[newloc[1]][newloc[2]].status == ALIVE && q->p[newloc[1]][newloc[2]].color == q->comp) {
								break;
							}
							else if(q->p[newloc[1]][newloc[2]].status == ALIVE && q->p[newloc[1]][newloc[2]].color != q->comp) {
								newloc[3] = KILL;
							}
							else {
								newloc[3] = NOKILL;
							}
							push(q, &q->s, loc, newloc);
							move1(q, loc, newloc, "exp");
							if(chcounter == 0) {
								valid = verifycheck(q);
								changestate(q);
								if(valid == CHECK) {
									if(loc[0] != KING) {
										i = 8;
										break;
									}
									continue;
								}
								else {
									if(loc[0] != KING) {
										chcounter = 1;
									}
								}
							}
							undoredo(q, "undowithoutredo");
							addtolist(t, loc, newloc);
						}
					}
					if(loc[0] == KING) {
						break;
					}
				}
				break;
		}
		if(p == KING) {
			break;
		}
		p++;
	}
	/* Now for pawn moves */
	prloc[0] = 0;
	newloc[0] = 0;
	newloc[3] = NOKILL;
	if(q->state == WHITE) {
		k = -1;
	}
	else {
		n1 = 1;
	}
	n2 = 0;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(n2 == 16) {
				break;
			}
			prloc[1] = i;
			prloc[2] = j;
			prloc[3] = NOKILL;
			if(q->p[i][j].name[1] == 'P' && q->p[i][j].color == q->state) {/* Pawn found */
				n2++;
				while(1) {
					if(q->p[i + n1][j].status != ALIVE) {
						newloc[1] = i + n1;
						newloc[2] = j;
						push(q, &q->s, prloc, newloc);
						move1(q, prloc, newloc, "exp");
						valid = verifycheck(q);
						changestate(q);
						undoredo(q, "undowithoutredo");
						if(valid == CHECK) {
							break;
						}
						addtolist(t, prloc, newloc);
						if((i == 3 && q->state == WHITE || i == 4 && q->state == BLACK) && q->p[i + n1 + n1][j].status != ALIVE) {
							newloc[1] = i + n1 + n1;
							addtolist(t, prloc, newloc);
						}
						break;
					}
				}
				newloc[3] = KILL;
				for(k = -1; k < 2; k = k + 2) {
					if(q->p[i + n1][j + k].status == ALIVE && q->p[i + n1][j + k].color == q->prevstate) {
						newloc[1] = i + n1;
						newloc[2] = j + k;
						push(q, &q->s, prloc, newloc);
						move1(q, prloc, newloc, "exp");
						valid = verifycheck(q);
						changestate(q);
						undoredo(q, "undowithoutredo");
						if(valid == CHECK) {
							break;
						}
						else {
							addtolist(t, prloc, newloc);
						}
					}
				}
			}
		}
	}
	//printw("Left genmoves");
	//getch();
	free(newloc);
	free(prloc);
}
