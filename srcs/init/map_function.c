/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:07:34 by sseo              #+#    #+#             */
/*   Updated: 2020/07/20 18:10:05 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_map(int ***map_ptr, int col_size)
{
	int		col_idx;

	col_idx = 0;
	while (col_idx < col_size)
	{
		free((*map_ptr)[col_idx]);
		col_idx++;
	}
	free(*map_ptr);
}

int			get_map_row_size(t_map_info *map_info)
{
	int				out;

	out = 0;
	while (map_info)
	{
		if (out < map_info->len)
			out = map_info->len;
		map_info = map_info->next;
	}
	return (out);
}

int			get_map_col_size(t_map_info *map_info)
{
	if (!map_info)
		return (print_error("wrong map info"));
	while (map_info->next)
		map_info = map_info->next;
	return (map_info->order + 1);
}

int			dfs(int **map, int **map_visit, int idx[2], int size[2])
{
	int		new_idx[2];
	int		i;
	int		j;

	if (idx[1] <= 0 || idx[1] >= size[1] - 1 || idx[0] <= 0 || idx[0] >= size[0] - 1)
		return (1);
	if (map[idx[1]][idx[0]] < 0)
		return (1);
	map_visit[idx[1]][idx[0]] = 1;
	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			new_idx[0] = idx[0] + i;
			new_idx[1] = idx[1] + j;
			if (map_visit[new_idx[1]][new_idx[0]] < 0 && map[new_idx[1]][new_idx[0]] != WALL)
				if (dfs(map, map_visit, new_idx, size))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}
