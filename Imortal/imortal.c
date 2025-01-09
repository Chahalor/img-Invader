/* Big Header */

#include "imortal.h"

// gcc -o imortal imortal->c -lX11

t_imortal	*Init_imortal(void)
{
	t_imortal	*imortal;

	imortal = (t_imortal *)calloc(1, sizeof(t_imortal));

	imortal->display = XOpenDisplay(NULL);
	if (imortal->display == NULL) {
		fprintf(stderr, "Impossible d'ouvrir la connexion X11\n");
		exit(X11_OPEN_DISPLAY_ERROR);
	}

	XMatchVisualInfo(imortal->display, DefaultScreen(imortal->display), 32, TrueColor, &imortal->vinfo);

	imortal->attr.colormap = XCreateColormap(imortal->display, DefaultRootWindow(imortal->display), imortal->vinfo.visual, AllocNone);
	imortal->attr.border_pixel = 0;
	imortal->attr.background_pixel = 0;

	imortal->height = 800;
	imortal->width = 800;
	imortal->x_pos = 0;
	imortal->y_pos = 0;
	imortal->win = XCreateSimpleWindow(imortal->display, DefaultRootWindow(imortal->display), 
									imortal->x_pos, imortal->y_pos, imortal->width, imortal->height, 0, 
									BlackPixel(imortal->display, DefaultScreen(imortal->display)), 
									WhitePixel(imortal->display, DefaultScreen(imortal->display)));
	imortal->gc = XCreateGC(imortal->display, imortal->win, 0, 0);

	XMapWindow(imortal->display, imortal->win);
	XSelectInput(imortal->display, imortal->win, KeyPressMask | KeyReleaseMask | ExposureMask);

	imortal->run = True;
	return (imortal);
}

/** @todo */
void	check_init(t_imortal *imortal)
{
	(void)imortal;
	/** @todo */
}

void	exiting(t_imortal *imortal)
{
	XDestroyWindow(imortal->display, imortal->win);
	XCloseDisplay(imortal->display);
	free(imortal);
}

void	IM_MOVE_WINDOW(t_imortal *imortal, int x, int y)
{
	XMoveWindow(imortal->display, imortal->win, x, y);
	imortal->x_pos = x;
	imortal->y_pos = y;
}

void	KeyPressedHandeler(t_imortal *imortal)
{
	KeySym	keysym = XLookupKeysym(&imortal->event.xkey, 0);
	printf("Key %s pressed\n", XKeysymToString(keysym));
	if (keysym == XK_Escape)
		imortal->run = False;
	else if (keysym == XK_Right)
		IM_MOVE_WINDOW(imortal, imortal->x_pos + 100, imortal->y_pos);
	else if (keysym == XK_Left)
		IM_MOVE_WINDOW(imortal, imortal->x_pos - 100, imortal->y_pos);
	else if (keysym == XK_Up)
		IM_MOVE_WINDOW(imortal, imortal->x_pos, imortal->y_pos - 100);
	else if (keysym == XK_Down)
		IM_MOVE_WINDOW(imortal, imortal->x_pos, imortal->y_pos + 100);
}

void	KeyReleasedHandeler(t_imortal *imortal)
{
	KeySym	keysym = XLookupKeysym(&imortal->event.xkey, 0);
	printf("Key %s released\n", XKeysymToString(keysym));
}


int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_imortal	*imortal = Init_imortal();
	check_init(imortal);
	while (imortal->run)
	{
		XNextEvent(imortal->display, &imortal->event);
		switch (imortal->event.type)
		{
			case ClientMessage:
				if (imortal->event.xclient.message_type == XInternAtom(imortal->display, "WM_PROTOCOLS", 1) 
				&& (Atom)imortal->event.xclient.data.l[0] == XInternAtom(imortal->display, "WM_DELETE_WINDOW", 1))
					imortal->run = False;
				break;
			case KeyPress:
				KeyPressedHandeler(imortal);
				break;
			case KeyRelease:
				KeyReleasedHandeler(imortal);
				break;
			case Expose:
				printf("Expose\n");
				break;
			default:
				break;
		}
	}
	exiting(imortal);
}
