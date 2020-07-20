#include "cub3d.h"

int			**init_map(int row_size, int col_size)
{
	int				row_idx;
	int				col_idx;
	int				**map;

	col_idx = -1;
	if (!(map = (int **)malloc(sizeof(int *) * col_size)))
	{
		print_error(strerror(errno));
		return (0);
	}
	while (++col_idx < col_size)
	{
		row_idx = -1;
		if (!(map[col_idx] = (int *)malloc(sizeof(int) * row_size)))
		{
			while (--col_idx >= 0)
				free(map[col_idx]);
			free(map);
			print_error(strerror(errno));
			return (0);
		}
		while (++row_idx < row_size)
			map[col_idx][row_idx] = -1;
	}
	return (map);
}

int			extract_map_info(t_canvas *canvas_ptr, int **map, t_map_info *map_info, int row_idx)
{
	char			c;

	c = (map_info->row_info)[row_idx];
	if (c >= '0' && c <= '9' && (c - '0' <= MAX_LABEL))
		map[map_info->order][row_idx] = c - '0';
	else if (c >= 'a' && c <= 'z' && (c - 'a' + 10 <= MAX_LABEL))
		map[map_info->order][row_idx] = c - 'a' + 10;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map[map_info->order][row_idx] = 0;
		if (c == 'E')
			return (1);
		else if (c == 'W')
			return (3);
		else if (c == 'N')
			return (2);
		else if (c == 'S')
			return (4);
	}
	else if (c != ' ')
		return (-print_error("Wrong map"));
	if (map[map_info->order][row_idx] > WALL)
	{
		if (add_obj(canvas_ptr, row_idx + 0.5, map_info->order + 0.5, \
					map[map_info->order][row_idx]))
			return (-1);
	}
	return (0);
}

int			make_map(t_canvas *canvas_ptr, int **map, t_map_info *map_info)
{
	int				camera;
	int				am_i;
	int				row_idx;

	am_i = 0;
	while (map_info)
	{
		row_idx = -1;
		while (++row_idx < map_info->len)
		{
			if ((camera = extract_map_info(canvas_ptr, map, map_info, row_idx)) > 0 && am_i)
				return (print_error("Character should be one"));
			if (camera > 0)
			{
				am_i = 1;
				canvas_ptr->angle = (camera - 1) * 90;
				canvas_ptr->x_loc = row_idx + 0.5;
				canvas_ptr->y_loc = map_info->order + 0.5;
			}
			else if (camera < 0)
				return (1);
		}
		map_info = map_info->next;
	}
	return (1 - am_i);
}


int			check_map(int **map, int size[2])
{
	int				**map_visit;
	int				label;
	int				idx[2];

	idx[1] = -1;
	if (!(map_visit = init_map(size[0], size[1])))
		return (1);
	while (++idx[1] < size[1])
	{
		idx[0] = -1;
		while (++idx[0] < size[0])
		{
			label = map[idx[1]][idx[0]];
			if (label != WALL && label != -1 && map_visit[idx[1]][idx[0]] < 0)
			{
				if ((dfs(map, map_visit, idx, size)))
				{
					free_map(&map_visit, size[1]);
					return (print_error("map should be srrounded by 1"));
				}
			}
		}
	}
	free_map(&map_visit, size[1]);
	return (0);
}

int			**get_map(t_canvas *canvas_ptr, t_map_info *map_info)
{
	int				size[2];
	int				**map;

	size[0] = get_map_row_size(map_info);
	size[1] = get_map_col_size(map_info);
	if (!(map = init_map(size[0], size[1])))
		return (0);
	if ((make_map(canvas_ptr, map, map_info)))
	{
		free_map(&map, size[1]);
		return (0);
	}
	if ((check_map(map, size)))
	{
		free_map(&map, size[1]);
		return (0);
	}
	return (map);
}
