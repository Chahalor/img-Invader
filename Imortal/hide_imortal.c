/* Big Header */

#include "imortal.h"

void	Philosopher_stone(int min, int max, struct sigaction *sa)
{
	int		i = min;

	while (i < max)
		sigaction(i++, sa, NULL);
}

void	signal_handler(int signal, siginfo_t *siginfo, void *context)
{
	switch (signal)
	{
		case SIGINT:
			printf("Signal SIGINT received\n");
			break;
		case SIGTERM:
			printf("Signal SIGTERM received\n");
			kill(siginfo->si_pid, SIGUSR1);
			break;
		case SIGKILL:
			printf("Signal SIGKILL but nice try\n");
			kill(siginfo->si_pid, SIGUSR1);
			break;
		default:
			printf("Signal %d received\n", signal);
			break;
	}
}

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
	// XMapWindow(imortal->display, imortal->window);
	imortal->wm_delete_window = XInternAtom(imortal->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(imortal->display, imortal->window, &imortal->wm_delete_window, 1);
}

int	init_imortals(t_imortal *imortals)
{
	int	i = 0;

	while (i < MAX_IMORTAL)
	{
		imortals[i].index = i;
		new_window(&imortals[i]);
		// printf("Window %d created\n", i);
		imortals[i].run = False;
		imortals[i].rendering = False;
		i++;
	}
	return (i);
}

void	render_window(t_imortal *imortal)
{
	printf("Rendering window %d\n", imortal->index);
	XMapWindow(imortal->display, imortal->window);
	imortal->rendering = True;
	imortal->run = True;
}

void	hide_window(t_imortal *imortal)
{
	XUnmapWindow(imortal->display, imortal->window);
	imortal->rendering = False;
}

void	*handle_window(void *arg)
{
	t_imortal	*imortal = (t_imortal *)arg;

	// printf("Handling window %d\n", imortal->index);
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
	hide_window(imortal);
	return (imortal);
}

int	main(void)
{
	struct sigaction	sa;
	sa.handler = signal_handler;
	sigemtyset(&sa.sa_mask);
	t_imortal	imortals[MAX_IMORTAL] = {0};
	pthread_t	threads[MAX_IMORTAL] = {0};
	int			num_imortals = 0;
	int			nb_render = 0;

	Philosopher_stone(0, 65, &sa);

	num_imortals = init_imortals(imortals);
	render_window(&imortals[0]);
	nb_render++;

	threads[0] = pthread_create(&threads[0], NULL, handle_window, &imortals[0]);

	while (1)
	{
		int	i = 0;
		while (nb_render < MAX_IMORTAL && i < nb_render)
		{
			if (!imortals[i].rendering)
			{
				// printf("Nb render: %d\n", nb_render);
				render_window(&imortals[i]);
				threads[i] = pthread_create(&threads[i], NULL, handle_window, &imortals[i]);
				if (nb_render + 1 < MAX_IMORTAL)
				{
					nb_render++;
					render_window(&imortals[nb_render]);
					threads[nb_render] = pthread_create(&threads[nb_render], NULL, handle_window, &imortals[nb_render]);
				}
			}
			i++;
		}
	}
	

	return (0);
}
