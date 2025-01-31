/* Big Header */

<<<<<<< HEAD
#include "imortal.h"

// gcc -o imortal imortal->c -lX11
=======
// >> gcc -o imortal imortal-v2.c -lX11

/* -----| Headers |----- */

#include "imortal.h"
>>>>>>> e8e0a55 (tkt)

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
<<<<<<< HEAD
	(void)imortal;
	/** @todo */
}

void	destroy(t_imortal *imortal)
{
	if (!imortal)
		return ;
	XDestroyWindow(imortal->display, imortal->win);
	XCloseDisplay(imortal->display);
	free(imortal);
	imortal = NULL;
=======
	/** @todo */
}

int	destroy(t_imortal *imortal)
{
	XDestroyWindow(imortal->display, imortal->win);
	XCloseDisplay(imortal->display);
	free(imortal);
	return (1);
>>>>>>> e8e0a55 (tkt)
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
<<<<<<< HEAD
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
=======
>>>>>>> e8e0a55 (tkt)
}

void	KeyReleasedHandeler(t_imortal *imortal)
{
	KeySym	keysym = XLookupKeysym(&imortal->event.xkey, 0);
	printf("Key %s released\n", XKeysymToString(keysym));
}

<<<<<<< HEAD
void *handle_window(void *arg) {
    t_imortal *imortal = (t_imortal *)arg;
    while (imortal->run) {
        while (XPending(imortal->display)) {
            XNextEvent(imortal->display, &imortal->event);
            switch (imortal->event.type) {
                case ClientMessage:
                    if (imortal->event.xclient.message_type == XInternAtom(imortal->display, "WM_PROTOCOLS", 1) 
                    && (Atom)imortal->event.xclient.data.l[0] == XInternAtom(imortal->display, "WM_DELETE_WINDOW", 1))
                        imortal->run = False;
                    break;
                case KeyPress:
                    // KeyPressedHandeler(imortal);
                    break;
                case KeyRelease:
                    // KeyReleasedHandeler(imortal);
                    break;
                case Expose:
                    printf("Expose\n");
                    break;
                case DestroyNotify:
                    imortal->run = False;
                    break;
                default:
                    break;
            }
        }
    }
    return NULL;
}

void handle_all_events(t_pantheon *Pantheon) {
    pthread_t threads[Pantheon->nb_imortal];
    for (unsigned int i = 0; i < Pantheon->nb_imortal; i++) {
        t_imortal *imortal = Pantheon->pantheon[i];
        imortal->run = True;
        if (pthread_create(&threads[i], NULL, handle_window, (void *)imortal) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }
    for (unsigned int i = 0; i < Pantheon->nb_imortal; i++) {
        pthread_join(threads[i], NULL);
    }
}


int main(int argc, char *argv[])
{
	(void)argc; // @todo
	(void)argv;
	t_pantheon *Pantheon = (t_pantheon *)calloc(1, sizeof(t_pantheon));
	if (!Pantheon)
	{
		perror("failed to allocate memory for Pantheon");
		return (EXIT_FAILURE);
	}
	Pantheon->nb_imortal = 0;
	while (Pantheon->nb_imortal < NB_NEW_IMORTAL)
	{
		Pantheon->pantheon[Pantheon->nb_imortal] = Init_imortal();
		Pantheon->nb_imortal++;
	}
	while (Pantheon->nb_imortal)
	{
		printf("Cycle\n");
		handle_all_events(Pantheon);
		unsigned int	i = 0;
		while (i < Pantheon->nb_imortal)
		{
			if (!Pantheon->pantheon[i]->run)
			{
				destroy(Pantheon->pantheon[i]);
				Pantheon->pantheon[i] = NULL;
				Pantheon->nb_imortal--;
				new_imortal(Pantheon);
			}
		}
	}
	free(Pantheon);
	return 0;
=======
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
>>>>>>> e8e0a55 (tkt)
}
