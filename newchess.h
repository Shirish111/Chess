
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

/* Header file containing all the #directives, typedefs, enums and function prototypes
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <limits.h>
#define PAWN_VAL 1
#define KNIGHT_VAL 3
#define BISHOP_VAL 3
#define ROOK_VAL 5
#define QUEEN_VAL 9
#define KING_VAL 11
#define DEPTH 1
#define min(X, Y) ((X) < (Y)? (X):(Y))
#define max(X, Y) ((X) > (Y)? (X):(Y))
typedef struct moves {
	int prloc[4];
	int locinput[4];
	struct moves *next, *previous;
}moves;
typedef struct moveslist {
	int count;
	moves *head, *tail;
}moveslist;
typedef struct tree {
	int loc[8];
	int score;
	moveslist *ml;
	int numchildren;
	struct tree **children;
	struct tree *parent;
}tree;
/* Checkgiver */
typedef struct chg {
	int a[4];
	int count;
}chg;
/* Stack */
typedef struct stacknode {
	int *prloc;/* Stores the previous location */
	int *locinput;/* Stores the next location */
	int *loc3;/* Stores the killed piece if any */
	int castle;/* Used to denote special moves like castling or npassant */
	struct stacknode *next, *previous;
}stacknode;
typedef struct stack {
	stacknode *head, *tail;
	int count;
}stack;
/* List */
typedef struct node {
	int loc[4];
	int color;
	int moved;
	struct node *next;
	struct node *previous;
}node;
typedef struct list {
	node *head, *tail;
	int count;
}list;
typedef struct coin {
	char name[2];
	int color;
	int status;
}coin;
typedef struct chess {
	coin *p[8];
	int count;
	int state, prevstate, enable, compplay, depth;
	struct list *l;
	stack s;/* For undo */
	stack r;/* For redo */
	chg c;/* Checkgiver */
	int pieceeval[12][8][8];
	int comp;
	tree *t;
}chess;
enum en{WHITE = 1, BLACK = 2, NOCOLOR = 3, ALIVE = 4, NOSTATUS = 5, PAWN = 123, KNIGHT, BISHOP, ROOK, QUEEN, KING, DEAD = 81, CONF = 82, WIN = 1000, LOSE = 1001, DRAW = 1002, CHECK = 200, NOCHECK, CHECKMATE, NOCHECKMATE, KILL = 500, NOKILL, NOTFOUND = 1234, NOTHING = 1111, MOVED, NOTMOVED, CASTLE, QUITW, NPASS, STALEMATE, THREEFOLD_REPETITION, FIFTY_STEPS_RULE, INSUFFICIENT_MATERIAL, ENABLE, DISABLE};
/* Player vs Player mode */
int p_vs_p_mode(WINDOW *);
void init(chess *q);/* Initialization */
void display1(WINDOW *win);
int display2(WINDOW *win);
void display(WINDOW *win, chess *q);
int comp_vs_p_mode (WINDOW *win, int n);
int display_help_about(WINDOW *win, char *str);/* Displays help and about */
char *getuserinput(WINDOW *win);/* Gets user input as a string and returns the string */
int* getinputlocation(chess *q, char *str);/* Converts the string to an integer */
int *correctness(chess *q, int *locinput);/* Checks the correctness of the location(called by getinputlocation()) */
int* getinputlocationpr(chess *q, char *str, int *loc);
int converti(char c);/* Converts the ith column into an int */
int convertj(char c);/* Converts the jth column into an int */
int convertp(char c);/* Converts the piece(char) into an int */
char rconvertp(int c);/* Converts the int to a char */
int *pawnsearch(chess *q, int *locinput);/* Searches the location of the pawn */
int *getpreviousloc(chess *q, int *locinput, int chk);/* Gets previous location of a piece when the next location is specified */
int *checkifvalid(chess *q, int *locinput, int *prloc, int ch);/* Checks for matches and barriers */
void changestate(chess *q);/* Changes the state from WHITE to BLACK and vice versa */
void writetofile(chess *q, char *str);/* Writes moves into a file */
void printstate(WINDOW *win, chess *q);/* Prints the current state */
void convprint(int *loc);/* Converts the location into strings and prints */
int match(chess *q, int *prloc, int *locinput);/* Compares loc1 and loc2 for a match and returns appropriate output  */
int barrier(chess *q, int *loc1, int *loc2, int chk);/* Verifies if there is a barrier between loc1 and loc2 */
int *undoredo(chess *q, char *str);/* For undo and redo */
char concolor(int state);/* If the color is white returns W else returns B */
int verifycheck(chess *q);/* Verifies check */
int checkfromall(chess *q, int *kingloc);/* Verifies check from all pieces except pawns */
int checkfrompawns(chess *q, int *prloc);/* Verifies check from pawns */
/* All list functions */
void initlist(chess *q);/* Will initialize the list with the locations and details of pieces except pawns */
void printlist(chess *q);/* Prints the list */
int *search(chess *q, int name, int color, int* moved1, int *moved2);/* Searches the location of the piece and also returns if it was moved */
int remov(chess *q, int *loc);/* Removes a piece from the list */
int update(chess *q, int *prev, int* new);/* If the location of a piece is changed then it upadates the location of the piece */
int append(chess *q, int *loc, int color);/* Appends the piece in case of pawn promotion or an undo redo */
/* All stack functions */
void initstack(stack *s);/* Initializes the stack */
void push(chess *q, stack *s, int *prloc, int *locinput);/* Pushes the location into stack */
int *pop(chess *q, stack *s);/* Pops the locations from the stack */
int empty(stack *s);/* checks if the stack is empty */
void printstack(stack *s);/* prints the stack */
void freeredo(chess *q, stack *s);/* Frees redo stack */
int castling(chess *q, char *str);/* For castling */
void copyloc(chg *c, int *loc);/* For copying the location */
int declarewinner(chess *q);/* Declares the winner */
void unmove(chess *, int *, char *);/* Unmoves */
void pawnpromotion(chess *q);/* For Pawn promotion */
int resign(chess *q);/* If the player wants to resign */
void readfromfile(chess *q);/* Reads moves from file */
void move1(chess *q, int *prloc, int *locinput, char *str);/* For piece movement on the board */
void openmoves(chess *q);/* If you want to open an already saved file(moves) */
void savefile(chess *q);/* Saves moves to a file */
void printcoinw(WINDOW *win, int y, int x, char *str);/* Prints the coins on the board(utf characters for pieces) */
void addvisited(int **visited, int n, int n1, int n2);/* Adds that a location is visited in a 2d array (used for draw condition) */
int visitedf(int **visited, int n, int n1, int n2);/* Returns 1 if the location is visited */
int *piecesearchlist(chess *q, int *prloc);/* Searches the piece and returns the location */
int piecesmove(chess *q);/* Checks if the piece can be moved legally */
void enable(chess *q, char *str);/* Used as a counter to disable or enable some printing */
int declaredraw(chess *q, char *str);/* Declares draw */
int eval(chess *q);
void generatemoves(chess *q, tree *t);
void initmoveslist(tree *t);
void addtolist(tree *t, int *prloc, int *locinput);
void inittree(tree **t);
void insertnodes(tree **t, moveslist *l, int depth);
void compmove(chess *q);
int build(chess *q, tree **t, int start);
