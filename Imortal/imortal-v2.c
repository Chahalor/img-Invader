/* Big Header */

// >> gcc -o imortal imortal-v2.c -lX11

/* -----| Headers |----- */

#include "imortal.h"

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
	/** @todo */
}

int	destroy(t_imortal *imortal)
{
	XDestroyWindow(imortal->display, imortal->win);
	XCloseDisplay(imortal->display);
	free(imortal);
	return (1);
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
}

void	KeyReleasedHandeler(t_imortal *imortal)
{
	KeySym	keysym = XLookupKeysym(&imortal->event.xkey, 0);
	printf("Key %s released\n", XKeysymToString(keysym));
}

int	day_manager(t_imortal *imortal)
{
	XNextEvent(imortal->display, &imortal->event);
	switch (imortal->event.type)
	{
		case ClientMessage:
			if (imortal->event.xclient.message_type == XInternAtom(imortal->display, "WM_PROTOCOLS", 1) 
				&& (Atom)imortal->event.xclient.data.l[0] == XInternAtom(imortal->display, "WM_DELETE_WINDOW", 1))
				return (destroy(imortal));
		break;
		case DestroyNotify:
			destroy(imortal);
			break;
		case KeyPress:
			KeyPressedHandeler(imortal);
			break;
		case KeyRelease:
			KeyReleasedHandeler(imortal);
			break;
		case Expose:
			break;
	}
}

int	main(int argc, const char *argv[])
{
	int	nb_imortal = 0;
	if (argc > 1)
		nb_imortal = atoi(argv[1]);
	else
		nb_imortal = NB_NEW_IMORTAL;
	
	t_imortal	**pantheon = (t_imortal **)calloc(nb_imortal, sizeof(t_imortal *));
	int	i = 0;
	while (i < nb_imortal)
	{
		pantheon[i] = Init_imortal();
		i++;
	}
	while (True)
	{
		i = 0;
		while (i < nb_imortal)
		{
			int action = day_manager(pantheon[i]);
			if (action == 1)
			{
				pantheon[i] = NULL;
				nb_imortal--;
			}
			i++;
		}
	}
}
