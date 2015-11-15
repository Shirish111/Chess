
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

Project : CHESS
Name    : SHIRISHKUMAR TOGARLA
MISID   : 111408061

	In this project I have tried to include all the standard rules of chess. I have used list, stack and tree datastructures in the project. The features of my project are :

1. Graphical User Interface
	I used NCURSES to provide the graphical user interface.

2. Ease of playing
	Most of the time you have to just enter the next location and the program will search for a matching previous 
location and will make a valid move.

3. Strict Rules
	I have tried to include all the rules of chess. These are written in the help which will appear on running the project(game).

4. Other features
	They include saving the moves which you played during the game. Opening an already saved file(containing moves of chess which was saved earlier).
	I have used two stacks for undoing and redoing of the moves. I have used a list datastructure to store all the locations of the pieces except pawns because searching the entire board will affect the performance of the game.
I have used a tree to make the computer play(presently not working). I have used other ways to tackle with special moves like npassant, castling(both long castle and short castle), pawn promotion, etc. Presently my project supports the following things :

1. Detects CHECK (and conveys from where it is coming)

2. Performs NPASSANT

3. Performs CASTLING(both long castle and short castle)

4. Detects CHECKMATE

5. Detects DRAW

	This includes the following conditions:
	1. STALEMATE

	2. THREEFOLD_REPETITION

	3. INSUFFICIENT_MATERIAL

	4. 50_STEPS_RULE

6. Exchange of pieces (or killing a piece)

7. Verifies if the move is valid

8. Undo and Redo

9. Save moves

10. Open an already saved moves list
