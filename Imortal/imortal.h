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
#define NUM_IMORTALS 1
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
	Atom	wm_delete_window;
	int		index;
}			t_imortal;

/* -----| Functions |----- */

void *handle_window(void *arg);


