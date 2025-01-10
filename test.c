#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Ouverture de la connexion à X11
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Impossible d'ouvrir la connexion X11\n");
        return 1;
    }

    // Récupération des informations sur l'écran
    int screen = DefaultScreen(display);

    // Création d'une fenêtre
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 
                                        100, 100, 800, 600, 1, 
                                        BlackPixel(display, screen), WhitePixel(display, screen));

    // Créer le contexte graphique
    GC gc = XCreateGC(display, window, 0, NULL);

    // Rendre la fenêtre visible
    XMapWindow(display, window);

    // Sélectionner les événements que l'on souhaite écouter (ici les événements de clavier)
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask | ExposureMask);

    // Boucle principale
    int quit = 0;
    XEvent event;
    while (!quit) {
        // Attente d'un événement
        XNextEvent(display, &event);

        // Gérer l'événement de fermeture
        if (event.type == Expose) {
            // Dessiner quelque chose dans la fenêtre quand elle est exposée
            XFillRectangle(display, window, gc, 100, 100, 600, 400);
        }

        // Détection d'une pression sur une touche
        if (event.type == KeyPress) {
            KeySym keysym = XLookupKeysym(&event.xkey, 0); // Obtenir la touche pressée

            // Afficher quelle touche a été pressée
            printf("Touche pressée: %s\n", XKeysymToString(keysym));

            // Quitter le programme si 'q' est pressée
            if (keysym == XK_q) {
                quit = 1;
            }
        }

        // Détection du relâchement d'une touche
        if (event.type == KeyRelease) {
            KeySym keysym = XLookupKeysym(&event.xkey, 0); // Obtenir la touche relâchée

            // Afficher quelle touche a été relâchée
            printf("Touche relâchée: %s\n", XKeysymToString(keysym));
        }
    }

    // Nettoyage
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h> // Ajouter cette ligne pour utiliser les atomes EWMH

#include <string.h>
#include <stdio.h>

// gcc -o imortal imortal.c -lX11

void	exiting(Display* display, Window win)
{
	XDestroyWindow(display, win);
	XCloseDisplay(display);
}

void	KeyPressedHandeler(Display* display, Window win, XEvent event)
{
	KeySym	keysym = XLookupKeysym(&event.xkey, 0);
	printf("Key %s pressed\n", XKeysymToString(keysym));
}

void	KeyReleasedHandeler(Display* display, Window win, XEvent event)
{
	KeySym	keysym = XLookupKeysym(&event.xkey, 0);
	printf("Key %s released\n", XKeysymToString(keysym));
}

int main(int argc, char* argv[])
{
	Display* display = XOpenDisplay(NULL);	// init display
	if (display == NULL) {
		fprintf(stderr, "Cannot open display\n");
		return 1;
	}

	XVisualInfo vinfo;	// visual info
	XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);

	XSetWindowAttributes attr;	// window attributes
	attr.colormap = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
	attr.border_pixel = 0;
	attr.background_pixel = 0;

	// Create window
	int	height = 1080;
	int	width = 1920;
	Window win = XCreateWindow(display, DefaultRootWindow(display), 0, 0, width, height, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);
	XSelectInput(display, win, StructureNotifyMask);
	GC gc = XCreateGC(display, win, 0, 0);

	// Set WM_PROTOCOLS and WM_DELETE_WINDOW
	Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(display, win, &wm_delete_window, 1);

	// Définir la position de la fenêtre (par exemple, à 100, 100)

	XMapWindow(display, win);	// Display window

	int x_position = 800;
	int y_position = 800;
	XMoveWindow(display, win, x_position, y_position);

	//Set Fullscreen
	Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
	Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

	XEvent xev;	// Event
	memset(&xev, 0, sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = win;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;

	// Send event
	XSendEvent(display, DefaultRootWindow(display), False, SubstructureNotifyMask, &xev);

	int keep_running = 1;
	XEvent event;

	while (keep_running) {
		XNextEvent(display, &event);

		switch(event.type) {
			case ClientMessage:
				if (event.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", 1) && (Atom)event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", 1))
					keep_running = 0;
				break;
			case ConfigureNotify:
				width = event.xconfigure.width;
				height = event.xconfigure.height;
				break;
			case KeyPress:
				KeyPressedHandeler(display, win, event);
				break;
			case KeyRelease:
				KeyReleasedHandeler(display, win, event);
				break;
			default:
				break;
		}
	}

	XDestroyWindow(display, win);
	XCloseDisplay(display);

	return 0;
}