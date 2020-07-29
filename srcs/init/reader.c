/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:25:40 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 09:29:19 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			get_path_info(t_canvas *canvas_ptr, const char *line)
{
	if (*line == 'R')
		return (get_resolution(canvas_ptr, line + 1));
	else if (*line == 'N' && *(line + 1) == 'O')
		return (get_wall_texture(canvas_ptr, line + 2, NORTH));
	else if (*line == 'S' && *(line + 1) == 'O')
		return (get_wall_texture(canvas_ptr, line + 2, SOUTH));
	else if (*line == 'W' && *(line + 1) == 'E')
		return (get_wall_texture(canvas_ptr, line + 2, WEST));
	else if (*line == 'E' && *(line + 1) == 'A')
		return (get_wall_texture(canvas_ptr, line + 2, EAST));
	else if (*line == 'C')
		return (get_wall_texture(canvas_ptr, line + 1, UP));
	else if (*line == 'F')
		return (get_wall_texture(canvas_ptr, line + 1, DOWN));
	else if (*line == 'S')
		return (get_object_texture(canvas_ptr, line + 1));
	else
		return (print_error("Wrong Identifier"));
}

int			file_reader(t_canvas *canvas_ptr, char *file_name)
{
	int			fd;
	int			gnl_ans;
	int			is_error;
	char		*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (print_error(strerror(errno)));
	while ((gnl_ans = get_next_line(fd, &line)) > 0 && \
			!(is_map_line((const char *)line)))
	{
		if (*line >= 65 && *line <= 90)
			is_error = get_path_info(canvas_ptr, (const char *)line);
		else
			is_error = 1 - is_empty_line((const char *)line);
		free(line);
		if (is_error)
			return (1);
	}
	if (gnl_ans == 0)
		free(line);
	if (gnl_ans <= 0)
		return (print_error("Wrong map"));
	return (map_reader(canvas_ptr, fd, &line));
}

void		free_map_info(t_map_info **map_info)
{
	t_map_info	*current;
	t_map_info	*after;

	current = *map_info;
	after = current;
	while (current)
	{
		after = current->next;
		free((void *)current->row_info);
		free(current);
		current = after;
	}
	*map_info = 0;
}

int			get_map_info(t_map_info **map_info, char **line)
{
	static int	order;
	t_map_info	*new;
	t_map_info	*temp;

	temp = *map_info;
	if (!(new = (t_map_info *)malloc(sizeof(t_map_info))))
	{
		free_map_info(map_info);
		free(*line);
		return (print_error(strerror(errno)));
	}
	if (*map_info == 0)
		order = 0;
	new->order = order;
	new->len = search_idx((const char *)*line, 0);
	new->row_info = *line;
	new->next = 0;
	map_info_insert_last(map_info, &new);
	order++;
	return (0);
}

int			map_reader(t_canvas *canvas_ptr, int fd, char **line)
{
	int			gnl_ans;
	int			**map;
	t_map_info	*map_info;

	map_info = 0;
	if (get_map_info(&map_info, line))
		return (1);
	while ((gnl_ans = get_next_line(fd, line)) > 0)
		if (get_map_info(&map_info, line))
			return (1);
	if (gnl_ans < 0)
	{
		free_map_info(&map_info);
		return (print_error("GNL fail"));
	}
	if (get_map_info(&map_info, line))
		return (1);
	map = get_map(canvas_ptr, map_info);
	free_map_info(&map_info);
	if (!map)
		return (1);
	canvas_ptr->map = map;
	return (0);
}
