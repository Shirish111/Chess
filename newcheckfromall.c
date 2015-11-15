
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

/*This file include the function checkfromall() which verifies if there is a check from all other pieces except from pawns
 */
#include "newchess.h"
int checkfromall(chess *q, int *kingloc) {
	int *loc,i;
	q->c.count = 0;
	//Changing  the state just to get the required piece
	changestate(q);
	kingloc[0] = ROOK;//Changing the name to get the previouslocation
	loc = getpreviousloc(q, kingloc, CHECK);//See if the piece can be put in the kingloc. If yes then king is in check
	loc = checkifvalid(q, kingloc, loc, CHECK);
	if(loc != NULL) {
		//Just save the location
		if(q->enable == ENABLE) {
			mvprintw(20, 110, "CHECK from ROOK");	
		}
		copyloc(&q->c, loc);
		q->c.count++;
	}
	kingloc[0] = BISHOP;
	loc = getpreviousloc(q, kingloc, CHECK);
	loc = checkifvalid(q, kingloc, loc, CHECK);
	if(loc != NULL) {
		if(q->enable == ENABLE) {
			mvprintw(20, 110, "CHECK from BISHOP");	
		}
		if(q->c.count == 1) {
			(q->c.count)++;
			changestate(q);
			return CHECK;
		}
		else {
			//Save the location
			copyloc(&q->c, loc);
			(q->c.count)++;
		}
	}
	kingloc[0] = KNIGHT;
	loc = getpreviousloc(q, kingloc, CHECK);
	loc = checkifvalid(q, kingloc, loc, CHECK);
	if(loc != NULL) {
		if(q->enable == ENABLE) {
			mvprintw(20, 110, "CHECK from KNIGHT");
		}
		if(q->c.count == 1) {
			(q->c.count)++;
			changestate(q);
			return CHECK;
		}
		else {
			//Save the location
			copyloc(&q->c, loc);
			(q->c.count)++;
		}
	}
	kingloc[0] = QUEEN;
	loc = getpreviousloc(q, kingloc, CHECK);
	loc = checkifvalid(q, kingloc, loc, CHECK);
	if(loc != NULL) {
		if(q->enable == ENABLE) {
			mvprintw(20, 110, "CHECK from QUEEN");
		}
		if(q->c.count == 1) {
			(q->c.count)++;
			changestate(q);
			return CHECK;
		}
		else {
			//Save the location
			copyloc(&q->c, loc);
			(q->c.count)++;
		}
	}
	kingloc[0] = KING;
	loc = getpreviousloc(q, kingloc, CHECK);
	loc = checkifvalid(q, kingloc, loc, CHECK);
	if(loc != NULL) {
		if(q->enable == ENABLE) {
			mvprintw(20, 110, "CHECK from KING");	
		}
		//Save the location
		copyloc(&q->c, loc);
		(q->c.count)++;
		changestate(q);
		return CHECK;
	}
	changestate(q);
	if(q->c.count == 0) {
		return NOCHECK;
	}
	return CHECK;
}
