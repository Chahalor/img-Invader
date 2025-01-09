/* Big Header */
#pragma once

/* -----| Library |----- */

#include <X11/Xlib.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>


/* -----| Headers |----- */
//...

/* -----| Constants |----- */

#define IMORTAL_VERSION "0.0.1"
#define NB_NEW_IMORTAL 2
#define MAX_IMORTAL 100

/* -----| Macros |----- */
//...

/* -----| Enums |----- */

/** @todo */
typedef enum e_error
{
	NO_ERROR = 0,
	X11_OPEN_DISPLAY_ERROR,
	IMOR_INIT_ERROR,
	IMPOSSIBLE_TO_OPEN_X11_CONNECTION,
}	t_error;

/* -----| Structs |----- */

typedef struct s_imortal {
	Display	*display;
	Window	window;
	XEvent	event;
	Bool	run;
}			t_imortal;

typedef struct s_pantheon
{
	t_imortal		pantheon[MAX_IMORTAL];
	unsigned int	nb_imortal;
}					t_pantheon;


/* -----| Functions |----- */

// debug.c

void		print_imortal(t_imortal *him);
void		print_pantheon(t_pantheon *pantheon);

