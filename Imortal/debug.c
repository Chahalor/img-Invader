/* Big Header */

#include "imortal.h"

void	print_imortal(t_imortal *him)
{
	printf("Display: %p\n", him->display);
	printf("Run: %d\n", him->run);
	printf("XEvent: %p\n", &him->event);

}

void	print_pantheon(t_pantheon *pantheon)
{
	unsigned int i = 0;

	printf("Pantheon:\n");
	printf("Nb imortal: %u\n", pantheon->nb_imortal);
	while (i < pantheon->nb_imortal)
	{
		printf("Imortal %u:\n", i);
		print_imortal(pantheon->pantheon[i]);
		i++;
	}
}
