
/*
 * TINT - TINT Is Not Tetris
 * Copyright (c) 2001-2025 Abraham van der Merwe <abz@frogfoot.com>
 * 
 * This file is distributed under the terms of the MIT License.
 * See the LICENSE file in the project root for full license text.
 */

#include <stdarg.h>		/* va_list(), va_start(), va_end() */
#include <sys/time.h>	/* gettimeofday() */
#include <unistd.h>		/* gettimeofday() */

#include <curses.h>

#include "io.h"

/* Number of colors defined in io.h */
#define NUM_COLORS	8

/* Number of attributes defined in io.h */
#define NUM_ATTRS	9

/* Cursor definitions */
#define CURSOR_INVISIBLE	0
#define CURSOR_NORMAL		1

/* Maps color definitions onto their real definitions */
static int color_map[NUM_COLORS];

/* Maps attribute definitions onto their real definitions */
static int attr_map[NUM_ATTRS];

/* Current attribute used on screen */
static int out_attr;

/* Current color used on screen */
static int out_color;

/* This is the timeout in microseconds */
static int in_timetotal;

/* This is the amount of time left to before a timeout occurs (in microseconds) */
static int in_timeleft;

/*
 * Init & Close
 */

/* Initialize screen */
void io_init()
{
   initscr();
   start_color();
   curs_set(CURSOR_INVISIBLE);
   out_attr = A_NORMAL;
   out_color = COLOR_WHITE;
   noecho();
   /* Map colors */
   color_map[COLOR_BLACK] = COLOR_BLACK;
   color_map[COLOR_RED] = COLOR_RED;
   color_map[COLOR_GREEN] = COLOR_GREEN;
   color_map[COLOR_YELLOW] = COLOR_YELLOW;
   color_map[COLOR_BLUE] = COLOR_BLUE;
   color_map[COLOR_MAGENTA] = COLOR_MAGENTA;
   color_map[COLOR_CYAN] = COLOR_CYAN;
   color_map[COLOR_WHITE] = COLOR_WHITE;
   /* Map attributes */
   attr_map[ATTR_OFF] = A_NORMAL;
   attr_map[ATTR_BOLD] = A_BOLD;
   attr_map[ATTR_DIM] = A_DIM;
   attr_map[ATTR_UNDERLINE] = A_UNDERLINE;
   attr_map[ATTR_BLINK] = A_BLINK;
   attr_map[ATTR_REVERSE] = A_REVERSE;
   attr_map[ATTR_INVISIBLE] = A_INVIS;
}

/* Restore original screen state */
void io_close()
{
   echo();
   attrset(A_NORMAL);
   clear();
   curs_set(CURSOR_NORMAL);
   refresh();
   endwin();
}

/*
 * Output
 */

/* Set color attributes */
void out_setattr(int attr)
{
   out_attr = attr_map[attr];
}

/* Set color */
void out_setcolor(int fg, int bg)
{
   out_color = (color_map[bg] << 3) + color_map[fg];
   init_pair(out_color, color_map[fg], color_map[bg]);
   attrset(COLOR_PAIR(out_color) | out_attr);
}

/* Move cursor to position (x,y) on the screen. Upper corner of screen is (0,0) */
void out_gotoxy(int x, int y)
{
   move(y, x);
}

/* Put a character on the screen */
void out_putch(char ch)
{
   addch(ch);
}

/* Put a string on the screen */
void out_printf(char *format, ...)
{
   va_list ap;
   va_start(ap, format);
   vw_printw(stdscr, format, ap);
   va_end(ap);
}

/* Refresh screen */
void out_refresh()
{
   refresh();
}

/* Get the screen width */
int out_width()
{
   return COLS;
}

/* Get the screen height */
int out_height()
{
   return LINES;
}

/* Beep */
void out_beep()
{
   beep();
}

/*
 * Input
 */

/* Read a character. Please note that you MUST call in_timeout() before in_getch() */
int in_getch()
{
   struct timeval starttv,endtv;
   int ch;
   timeout(in_timeleft / 1000);
   gettimeofday(&starttv, NULL);
   ch = getch();
   gettimeofday(&endtv, NULL);
   /* Timeout? */
   if (ch == ERR)
	 in_timeleft = in_timetotal;
   /* No? Then calculate time left */
   else
	 {
		endtv.tv_sec -= starttv.tv_sec;
		endtv.tv_usec -= starttv.tv_usec;
		if (endtv.tv_usec < 0)
		  {
			 endtv.tv_usec += 1000000;
			 endtv.tv_sec--;
		  }
		in_timeleft -= endtv.tv_usec;
		if (in_timeleft <= 0) in_timeleft = in_timetotal;
	 }
   return ch;
}

/* Set keyboard timeout in microseconds */
void in_timeout(int delay)
{
   /* ncurses timeout() function works with milliseconds, not microseconds */
   in_timetotal = in_timeleft = delay;
}

/* Empty keyboard buffer */
void in_flush()
{
   flushinp();
}

