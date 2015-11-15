
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
/*This file contains the code to evaluate the board
*/
#include "newchess.h"
int eval(chess *q) {
	int i, j, scorew = 0, scoreb = 0;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			if(q->p[i][j].status == ALIVE) {
				switch(q->p[i][j].name[1]) {
					case PAWN:
						if(q->p[i][j].name[0] == 'W') {
							scorew += PAWN_VAL + PAWN_VAL * q->pieceeval[0][i][j];
						}
						else {
							scoreb += PAWN_VAL + PAWN_VAL * q->pieceeval[6][i][j];
						}
						break;
					case KNIGHT:
						if(q->p[i][j].name[0] == 'W') {
							scorew += KNIGHT_VAL + KNIGHT_VAL * q->pieceeval[1][i][j];
						}
						else {
							scoreb += KNIGHT_VAL + KNIGHT_VAL * q->pieceeval[7][i][j];
						}
						break;
					case BISHOP:
						if(q->p[i][j].name[0] == 'W') {
							scorew += BISHOP_VAL + BISHOP_VAL * q->pieceeval[2][i][j];
						}
						else {
							scoreb += BISHOP_VAL + BISHOP_VAL * q->pieceeval[8][i][j];
						}
						break;
					case ROOK:
						if(q->p[i][j].name[0] == 'W') {
							scorew += ROOK_VAL + ROOK_VAL * q->pieceeval[3][i][j];
						}
						else {
							scoreb += ROOK_VAL + ROOK_VAL * q->pieceeval[9][i][j];
						}
						break;
					case QUEEN:
						if(q->p[i][j].name[0] == 'W') {
							scorew += QUEEN_VAL + QUEEN_VAL * q->pieceeval[4][i][j];
						}
						else {
							scoreb += QUEEN_VAL + QUEEN_VAL * q->pieceeval[10][i][j];
						}
						break;
					case KING: 
						if(q->p[i][j].name[0] == 'W') { 
							scorew += KING_VAL + KING_VAL * q->pieceeval[5][i][j]; 
						} 
						else { 
							scoreb += KING_VAL + KING_VAL * q->pieceeval[11][i][j]; 
						} 
						break; 
				}
			}
		}
	}
	if(q->prevstate == WHITE) {
		// printw("Returned wh from eval");
		//getch();
		return scorew - scoreb;
	}
	else {
		// printw("Returned b from eval");
		//getch();
		return scoreb - scorew;
	}
}
