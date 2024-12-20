/* Big Header */
#pragma once

/* -----| Library |----- */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* -----| Headers |----- */
//...

/* -----| Constants |----- */

#define IMORTAL_VERSION "0.0.1"
#define NB_NEW_IMORTAL 2

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

typedef struct s_imortal
{
	Display *display;
	Window win;
	GC gc;
	XVisualInfo vinfo;
	XSetWindowAttributes attr;
	int run;
	XEvent event;
	unsigned int	height;
	unsigned int	width;
	unsigned int x_pos;
	unsigned int y_pos;
}	t_imortal;



/* -----| Functions |----- */
//...