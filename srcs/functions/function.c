/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:58:34 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 18:54:16 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	struct timespec			current;
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
	write(1, "Error\n", 6);
	write(1, s, search_idx(s, 0));
	write(1, "\n", 1);
	return (1);
}
