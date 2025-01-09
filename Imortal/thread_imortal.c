/* Big Header */

#include "imortal.h"

// this one works with 1 and 2 windows after the first one is closed

// void *handle_window(void *arg)
// {
//     t_imortal *imortal = (t_imortal *)arg;
//     while (imortal->run) {
//         while (XPending(imortal->display)) {
//             XNextEvent(imortal->display, &imortal->event);
//             switch (imortal->event.type) {
//                 case ClientMessage:
//                     if (imortal->event.xclient.message_type == XInternAtom(imortal->display, "WM_PROTOCOLS", 1) 
//                     && (Atom)imortal->event.xclient.data.l[0] == XInternAtom(imortal->display, "WM_DELETE_WINDOW", 1))
//                         imortal->run = False;
//                     break;
//                 case KeyPress:
//                     // KeyPressedHandeler(imortal);
//                     break;
//                 case KeyRelease:
//                     // KeyReleasedHandeler(imortal);
//                     break;
//                 case Expose:
//                     printf("Expose\n");
//                     break;
//                 case DestroyNotify:
//                     imortal->run = False;
//                     break;
//                 default:
//                     break;
//             }
//         }
//     }
//     return NULL;
// }

// void create_window(t_imortal *imortal) {
//     imortal->window = XCreateSimpleWindow(imortal->display, DefaultRootWindow(imortal->display), 0, 0, 200, 200, 1, 0, 0);
//     Atom wmDelete = XInternAtom(imortal->display, "WM_DELETE_WINDOW", True);
//     XSetWMProtocols(imortal->display, imortal->window, &wmDelete, 1);
//     XSelectInput(imortal->display, imortal->window, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask);
//     XMapWindow(imortal->display, imortal->window);
// }

// void handle_all_events(t_pantheon *Pantheon) {
//     pthread_t threads[Pantheon->nb_imortal];
//     for (unsigned int i = 0; i < Pantheon->nb_imortal; i++) {
//         t_imortal *imortal = Pantheon->pantheon[i];
//         imortal->run = True;
//         if (pthread_create(&threads[i], NULL, handle_window, (void *)imortal) != 0) {
//             perror("Failed to create thread");
//             exit(EXIT_FAILURE);
//         }
//     }
//     for (unsigned int i = 0; i < Pantheon->nb_imortal; i++) {
//         pthread_join(threads[i], NULL);
//     }
// }

// int main() {
//     if (!XInitThreads()) {
//         fprintf(stderr, "Failed to initialize Xlib thread support\n");
//         return EXIT_FAILURE;
//     }

//     Display *display = XOpenDisplay(NULL);
//     if (display == NULL) {
//         fprintf(stderr, "Cannot open display\n");
//         return EXIT_FAILURE;
//     }

//     t_imortal imortal;
//     imortal.display = display;
//     imortal.run = True;

//     create_window(&imortal);

//     pthread_t thread;
//     if (pthread_create(&thread, NULL, handle_window, (void *)&imortal) != 0)
// 	{
//         perror("Failed to create thread");
//         return EXIT_FAILURE;
//     }

//     pthread_join(thread, NULL);

//     if (!imortal.run) {
//         t_imortal imortal1, imortal2;
//         imortal1.display = display;
//         imortal1.run = True;
//         create_window(&imortal1);

//         imortal2.display = display;
//         imortal2.run = True;
//         create_window(&imortal2);

//         pthread_t thread1, thread2;
//         if (pthread_create(&thread1, NULL, handle_window, (void *)&imortal1) != 0) {
//             perror("Failed to create thread");
//             return EXIT_FAILURE;
//         }
//         if (pthread_create(&thread2, NULL, handle_window, (void *)&imortal2) != 0) {
//             perror("Failed to create thread");
//             return EXIT_FAILURE;
//         }

//         pthread_join(thread1, NULL);
//         pthread_join(thread2, NULL);
//     }

//     XCloseDisplay(display);
//     return 0;
// }


void *handle_window(void *arg)
{
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

void create_window(t_imortal *imortal) {
	imortal->window = XCreateSimpleWindow(imortal->display, DefaultRootWindow(imortal->display), 0, 0, 200, 200, 1, 0, 0);
	Atom wmDelete = XInternAtom(imortal->display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(imortal->display, imortal->window, &wmDelete, 1);
	XSelectInput(imortal->display, imortal->window, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask);
	XMapWindow(imortal->display, imortal->window);
}

// void handle_all_events(t_pantheon *Pantheon)
// {
// 	pthread_t threads[Pantheon->nb_imortal];
// 	for (unsigned int i = 0; i < Pantheon->nb_imortal; i++) {
// 		t_imortal *imortal = Pantheon.pantheon[i];
// 		imortal->run = True;
// 		if (pthread_create(&threads[i], NULL, handle_window, (void *)imortal) != 0) {
// 			perror("Failed to create thread");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	for (unsigned int i = 0; i < Pantheon->nb_imortal; i++) {
// 		pthread_join(threads[i], NULL);
// 	}
// }

int main() {
	if (!XInitThreads()) {
		fprintf(stderr, "Failed to initialize Xlib thread support\n");
		return EXIT_FAILURE;
	}

	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Cannot open display\n");
		return EXIT_FAILURE;
	}

	t_pantheon Pantheon = {0};
	t_imortal imortal = Pantheon.pantheon[0];
	imortal.display = display;
	imortal.run = True;

	create_window(&imortal);

	pthread_t thread;
	if (pthread_create(&thread, NULL, handle_window, (void *)&imortal) != 0)
		return (perror("Failed to create thread"), EXIT_FAILURE);

	pthread_join(thread, NULL);

	if (!imortal.run) {
		t_imortal imortal1, imortal2;
		imortal1.display = display;
		imortal1.run = True;
		create_window(&imortal1);

		imortal2.display = display;
		imortal2.run = True;
		create_window(&imortal2);

		pthread_t thread1, thread2;
		if (pthread_create(&thread1, NULL, handle_window, (void *)&imortal1) != 0) {
			perror("Failed to create thread");
			return EXIT_FAILURE;
		}
		if (pthread_create(&thread2, NULL, handle_window, (void *)&imortal2) != 0) {
			perror("Failed to create thread");
			return EXIT_FAILURE;
		}

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	}

	XCloseDisplay(display);
	return 0;
}