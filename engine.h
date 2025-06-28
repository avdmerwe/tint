#ifndef ENGINE_H
#define ENGINE_H

/*
 * TINT - TINT Is Not Tetris
 * Copyright (c) 2001-2025 Abraham van der Merwe <abz@frogfoot.com>
 * 
 * This file is distributed under the terms of the MIT License.
 * See the LICENSE file in the project root for full license text.
 */

#include "typedefs.h"		/* bool */

/*
 * Macros
 */

/* Number of shapes in the game */
#define NUMSHAPES	7

/* Number of blocks in each shape */
#define NUMBLOCKS	4

/* Number of rows and columns in board */
#define NUMROWS	23
#define NUMCOLS	13

/* Wall id - Arbitrary, but shouldn't have the same value as one of the colors */
#define WALL 16

/*
 * Type definitions
 */

typedef int board_t[NUMCOLS][NUMROWS];

typedef struct
{
   int x,y;
} block_t;

typedef struct
{
   int color;
   int type;
   bool flipped;
   block_t block[NUMBLOCKS];
} shape_t,shapes_t[NUMSHAPES];

typedef struct
{
   int moves;
   int rotations;
   int dropcount;
   int efficiency;
   int droppedlines;
} status_t;

typedef struct engine_struct
{
   int curx,cury;									/* coordinates of current piece */
   int curshape,nextshape;							/* current & next shapes */
   int score;										/* score */
   shapes_t shapes;									/* shapes */
   board_t board;									/* board */
   status_t status;									/* current status of shapes */
   void (*score_function)(struct engine_struct *);	/* score function */
} engine_t;

typedef enum { ACTION_LEFT, ACTION_ROTATE, ACTION_RIGHT, ACTION_DROP } action_t;

/*
 * Global variables
 */

extern const shapes_t SHAPES;

/*
 * Functions
 */

/*
 * Initialize specified tetris engine
 */
void engine_init(engine_t *engine, void (*score_function)(engine_t *));

/*
 * Perform the given action on the specified tetris engine
 */
void engine_move(engine_t *engine, action_t action);

/*
 * Evaluate the status of the specified tetris engine
 *
 * OUTPUT:
 *   1 = shape moved down one line
 *   0 = shape at bottom, next one released
 *  -1 = game over (board full)
 */
int engine_evaluate(engine_t *engine);

#endif	/* #ifndef ENGINE_H */
