/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 16:56:47 by sseo              #+#    #+#             */
/*   Updated: 2020/07/20 18:02:13 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char		*check_resolution_line(const char *line, int *val, int max_val)
{
	int		num;

	num = 0;
	if (*line != ' ')
		return (0);
	while (*line == ' ')
		line++;
	while (*line >= '0' && *line <= '9')
	{
		num = num * 10 + *line - '0';
		if (num > max_val)
			num = max_val;
		line++;
	}
	*val = num;
	return (line);
}

int			get_resolution(t_canvas *canvas_ptr, const char *line)
{
	int		test;
	int		width;
	int		height;
	int		screen_width;
	int		screen_height;

	width = 0;
	height = 0;
	test = CGMainDisplayID();
	screen_width = CGDisplayPixelsWide(test);
	screen_height = CGDisplayPixelsHigh(test);
	if (!(line = (const char *)check_resolution_line(line, &width, screen_width)))
		return (print_error("Wrong resolution"));
	if (!(line = (const char *)check_resolution_line(line, &height, screen_height)))
		return (print_error("Wrong resolution"));
	while (*line == ' ')
		line++;
	if (width <= 0 || height <= 0 || *line != 0)
		return (print_error("Wrong resolution"));
	canvas_ptr->width = width;
	canvas_ptr->height = height - height / 10;
	canvas_ptr->hud_width = width;
	canvas_ptr->hud_height = height / 10;
	canvas_ptr->horizon_line = canvas_ptr->height / 2;
	return (0);
}

int			get_wall_texture(t_canvas *canvas_ptr, const char *line, int d)
{
	char			*texture_path;
	int				is_error;

	if (*line != ' ')
		return (1);
	if (!(texture_path = trim_space(line)))
		return (1);
	is_error = add_xpm_img(canvas_ptr, texture_path, WALL, d);
	free(texture_path);
	return (is_error);
}

const char		*extend_object_reader(const char *line, int *label, int *pose)
{
	uint64_t	num;

	num = 0;
	if ((*line >= 'a' && *line <= 'z') || (*line >= '0' && *line <= '9'))
	{
		if (*line >= 'a' && *line <= 'z')
			*label = *line - 'a' + 10;
		if (*line >= '0' && *line <= '9')
			*label = *line - '0';
		line++;
		if (*label > MAX_LABEL)
			return (0);
		if (*line >= '0' && *line <= '9')
		{
			while (*line >= '0' && *line <= '9')
			{
				num = num * 10 + *line - '0';
				if (num > INT_MAX)
					return (0);
				line++;
			}
		}
		*pose = (int)num;
	}
	return (line);
}

int			get_object_texture(t_canvas *canvas_ptr, const char *line)
{
	int				label;
	int				pose;
	char			*texture_path;
	int				is_error;

	label = DECO_1;
	pose = DEFAULT_POSE;
	if (EXTEND_VERSION)
	{
		if (!(line = extend_object_reader(line, &label, &pose)))
			return (print_error("Wrong label"));
	}
	if (*line != ' ')
		return (1);
	if (!(texture_path = trim_space(line)))
		return (1);
	is_error = add_xpm_img(canvas_ptr, texture_path, label, pose);
	free(texture_path);
	return (is_error);
}
