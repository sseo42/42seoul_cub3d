/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:09:59 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 18:44:36 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				is_map_line(const char *line)
{
	int			idx;

	idx = 0;
	while (line[idx] == ' ')
		idx++;
	if (line[idx] >= '0' && line[idx] <= '9')
		return (1);
	return (0);
}

int				is_empty_line(const char *line)
{
	char		exception;
	int			idx;

	exception = '#';
	idx = 0;
	while (line[idx] == ' ')
		idx++;
	if (line[idx] != 0 && line[idx] != exception)
		return (print_error("Wrong line") - 1);
	return (1);
}

char			*trim_space(const char *line)
{
	char		*out;
	int			idx;
	int			out_idx;
	int			start;
	int			end;

	idx = 0;
	while (line[idx] == ' ')
		idx++;
	start = idx;
	while (line[idx] != ' ' && line[idx] != 0)
		idx++;
	end = idx;
	if (!(out = (char *)malloc(sizeof(char) * (end - start + 1))))
	{
		print_error(strerror(errno));
		return (0);
	}
	out_idx = -1;
	while (++out_idx < end - start)
		out[out_idx] = line[start + out_idx];
	out[out_idx] = 0;
	return (out);
}

int				simple_atoi(char *target)
{
	int			idx;
	int			out;

	if (!target)
		return (-1);
	idx = 0;
	out = 0;
	while (target[idx] >= '0' && target[idx] <= '9')
	{
		out = out * 10 + target[idx] - '0';
		idx++;
	}
	if (target[idx] || out > 255)
	{
		free(target);
		return (-1);
	}
	free(target);
	return (out);
}

int				get_rgb(t_canvas *canvas_ptr, char *str, int d)
{
	int			comma[2];
	int			r;
	int			g;
	int			b;

	if ((comma[0] = search_idx((const char *)str, ',')) != -1)
		comma[1] = comma[0] + 1 + \
					search_idx((const char *)&(str[comma[0] + 1]), ',');
	if (comma[0] == -1 || comma[1] == -1)
		return (1);
	str[comma[0]] = 0;
	str[comma[1]] = 0;
	r = simple_atoi(trim_space((const char *)str));
	g = simple_atoi(trim_space((const char *)&str[comma[0] + 1]));
	b = simple_atoi(trim_space((const char *)&str[comma[1] + 1]));
	if (r < 0 || g < 0 || b < 0)
		return (1);
	add_color(canvas_ptr, WALL, d, (r << 16) + (g << 8) + b);
	return (0);
}
