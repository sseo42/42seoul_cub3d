#include "cub3d.h"

unsigned long	get_ms(struct timespec current)
{
	unsigned long			out;

	out = (unsigned long)(current.tv_sec * CLOCKS_PER_SEC) + \
		  (unsigned long)(current.tv_nsec * CLOCKS_PER_SEC / 1000000000);
	return (out);
}

int				wait_ending(unsigned long ms)
{
	struct					timespec current;
	static unsigned long	start_time;
	unsigned long			current_time;

	if (!start_time)
	{
		clock_gettime(CLOCK_MONOTONIC, &current);
		start_time = get_ms(current);
	}
	clock_gettime(CLOCK_MONOTONIC, &current);
	current_time = get_ms(current);
	if (current_time - start_time > ms)
		return (1);
	return (0);
}

int				print_error(const char *s)
{
	printf("Error\n%s\n", s);
	return (1);
}
