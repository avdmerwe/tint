#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/*
 * TINT - TINT Is Not Tetris
 * Copyright (c) 2001-2025 Abraham van der Merwe <abz@frogfoot.com>
 * 
 * This file is distributed under the terms of the MIT License.
 * See the LICENSE file in the project root for full license text.
 */

/*
 * Boolean definitions
 */

#ifndef bool
#define bool int
#endif

#if !defined(false) || (false != 0)
#define false	0
#endif

#if !defined(true) || (true != 0)
#define true	1
#endif

#if !defined(FALSE) || (FALSE != false)
#define FALSE	false
#endif

#if !defined(TRUE) || (TRUE != true)
#define TRUE	true
#endif

/*
 * Error flags
 */

#if !defined(ERR) || (ERR != -1)
#define ERR		-1
#endif

#if !defined(OK) || (OK != 0)
#define OK		0
#endif

#endif	/* #ifndef TYPEDEFS_H */
