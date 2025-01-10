/* Big Header */

#include "imortal.h"

// this one works with 1 and 2 windows after the first one is closed

// void	new_window(void *data)
// {
// 	t_imortal	*imortal = (t_imortal *)data;
// 	imortal->display = XOpenDisplay(NULL);
// 	if (!imortal->display)
// 		return (perror("XOpenDisplay"));
// 	imortal->window = XCreateSimpleWindow(imortal->display, RootWindow(imortal->display, 0),
// 						0, 0, 800, 600, 1, BlackPixel(imortal->display, 0),
// 						WhitePixel(imortal->display, 0));
// 	XSelectInput(imortal->display, imortal->window, ExposureMask | KeyPressMask);
// 	XMapWindow(imortal->display, imortal->window);
// 	imortal->wm_delete_window = XInternAtom(imortal->display, "WM_DELETE_WINDOW", False);
// 	XSetWMProtocols(imortal->display, imortal->window, &imortal->wm_delete_window, 1);
	
// }

// void	*handle_window(void *arg)
// {
// 	t_imortal	*imortal = (t_imortal *)arg;
// 	new_window(imortal);
// 	while (imortal->run)
// 	{
// 		XNextEvent(imortal->display, &imortal->event);
// 		switch (imortal->event.type)
// 		{
// 			case Expose:
// 				XFillRectangle(imortal->display, imortal->window, DefaultGC(imortal->display, 0), 20, 20, 10, 10);
// 				break;
// 			case KeyPress:
// 				imortal->run = False;
// 				break;
// 			case ClientMessage:
// 				if (imortal->event.xclient.data.l[0] == (long)imortal->wm_delete_window)
// 					imortal->run = False;
// 				break;
// 			default:
// 				break;
// 		}
// 	}
// 	XDestroyWindow(imortal->display, imortal->window);
// 	XCloseDisplay(imortal->display);
// 	return (NULL);
// }


// int	main(void)
// {
// 	t_imortal	imortals = {0};
// 	pthread_t	threads;
// 	new_window(&imortals);
// 	imortals.run = True;

// 	pthread_create(&threads, NULL, handle_window, &imortals);
// 	pthread_join(threads, NULL);

// 	while (imortals.run == False)
// 	{
// 		imortals.run = True;
// 		pthread_create(&threads, NULL, handle_window, &imortals);
// 		pthread_join(threads, NULL);
// 	}
// }

void	new_window(void *data)
{
	t_imortal	*imortal = (t_imortal *)data;
	imortal->display = XOpenDisplay(NULL);
	if (!imortal->display)
		return (perror("XOpenDisplay"));
	imortal->window = XCreateSimpleWindow(imortal->display, RootWindow(imortal->display, 0),
						0, 0, 800, 600, 1, BlackPixel(imortal->display, 0),
						WhitePixel(imortal->display, 0));
	XSelectInput(imortal->display, imortal->window, ExposureMask | KeyPressMask);
	XMapWindow(imortal->display, imortal->window);
	imortal->wm_delete_window = XInternAtom(imortal->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(imortal->display, imortal->window, &imortal->wm_delete_window, 1);
	
}

void	init_imortals(t_imortal imortals[MAX_IMORTAL], pthread_t threads[MAX_IMORTAL], int *num_imortals)
{
	int	i = 0;

	while (i < NUM_IMORTALS)
	{
		imortals[i].index = i;
		new_window(&imortals[i]);
		imortals[i].run = True;
		pthread_create(&threads[i], NULL, handle_window, &imortals[i]);
		*num_imortals += 1;
		i++;
	}
}

void	*handle_window(void *arg)
{
	t_imortal	*imortal = (t_imortal *)arg;
	new_window(imortal);
	while (imortal->run)
	{
		XNextEvent(imortal->display, &imortal->event);
		switch (imortal->event.type)
		{
			case Expose:
				XFillRectangle(imortal->display, imortal->window, DefaultGC(imortal->display, 0), 20, 20, 10, 10);
				break;
			case KeyPress:
				imortal->run = False;
				break;
			case ClientMessage:
				if (imortal->event.xclient.data.l[0] == (long)imortal->wm_delete_window)
					imortal->run = False;
				break;
			default:
				break;
		}
	}
	XDestroyWindow(imortal->display, imortal->window);
	XCloseDisplay(imortal->display);
	return (NULL);
}

void	add_imortal(t_imortal imortals[MAX_IMORTAL], pthread_t threads[MAX_IMORTAL], int *num_imortals)
{
	imortals[*num_imortals].index = *num_imortals;
	new_window(&imortals[*num_imortals]);
	imortals[*num_imortals].run = True;
	pthread_create(&threads[*num_imortals], NULL, handle_window, &imortals[*num_imortals]);
	*num_imortals += 1;
}

int	main(void)
{
	t_imortal	imortals[MAX_IMORTAL] = {0};
	pthread_t	threads[MAX_IMORTAL];
	int			num_imortals = NUM_IMORTALS;
	Bool		run = True;

	init_imortals(imortals, threads, &num_imortals);

	while (run)
	{
		int	i = 0;
		while (i < num_imortals)
		{
			if (imortals[i].run == False)
			{
				imortals[i].run = True;
				pthread_create(&threads[i], NULL, handle_window, &imortals[i]);
				int	j = 0;
				while (j < NB_NEW_IMORTAL)
				{
					add_imortal(imortals, threads, &num_imortals);
					j++;
				}
			}
			i++;
		}
	}
}