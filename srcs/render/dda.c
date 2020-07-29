/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 02:03:18 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 10:10:06 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		dda_init(t_canvas *canvas_ptr, double ray_vec[2], \
			int loc_int[4], double distance[4])
{
	loc_int[0] = (int)canvas_ptr->x_loc;
	loc_int[1] = (int)canvas_ptr->y_loc;
	distance[2] = 1 / fabs(ray_vec[0]);
	distance[3] = 1 / fabs(ray_vec[1]);
	if (ray_vec[0] < 0)
	{
		loc_int[2] = -1;
		distance[0] = (canvas_ptr->x_loc - loc_int[0]) * distance[2];
	}
	else
	{
		loc_int[2] = 1;
		distance[0] = (1.0 + loc_int[0] - canvas_ptr->x_loc) * distance[2];
	}
	if (ray_vec[1] < 0)
	{
		loc_int[3] = 1;
		distance[1] = (1.0 + loc_int[1] - canvas_ptr->y_loc) * distance[3];
	}
	else
	{
		loc_int[3] = -1;
		distance[1] = (canvas_ptr->y_loc - loc_int[1]) * distance[3];
	}
}

int			dda_loop(t_canvas *canvas_ptr, t_obj_info **obj_info, \
			int loc_int[4], double distance[4])
{
	int			side;
	int			label;
	t_obj		*obj;
	t_obj_info	*info_idx;

	while (1)
	{
		side = (distance[0] < distance[1]) ? 0 : 1;
		loc_int[side] += loc_int[side + 2];
		label = canvas_ptr->map[loc_int[1]][loc_int[0]];
		if (label == 1 || label == CLOSE_DOOR)
			break ;
		else if (label > 1)
		{
			obj = search_obj(canvas_ptr->objs, loc_int[0], loc_int[1]);
			if ((info_idx = search_obj_info(*obj_info, obj->id)))
				info_idx->update = 2;
			else if (put_obj_info(obj_info, obj, canvas_ptr->x_loc, \
						canvas_ptr->y_loc))
				exit(1);
		}
		distance[side] += distance[side + 2];
	}
	return (side);
}

void		dda(t_canvas *canvas_ptr, t_wall_info *wall_info, \
			t_obj_info **obj_info, double ray_vec[2])
{
	int			side;
	int			direct;
	int			loc_int[4];
	double		distance[4];
	double		hit_point;

	dda_init(canvas_ptr, ray_vec, loc_int, distance);
	side = dda_loop(canvas_ptr, obj_info, loc_int, distance);
	direct = ray_vec[side] < 0 ? side * 2 + 1 : side * 2;
	wall_info->wall_ptr = search_img(canvas_ptr->imgs, \
			(canvas_ptr->map)[loc_int[1]][loc_int[0]], direct);
	wall_info->distance = distance[side];
	wall_info->line_height = (int)(canvas_ptr->height / distance[side]);
	wall_info->draw_start = -wall_info->line_height / 2 + \
							canvas_ptr->horizon_line;
	wall_info->draw_end = wall_info->line_height / 2 + canvas_ptr->horizon_line;
	if (side)
		hit_point = (ray_vec[1] == 0) ? canvas_ptr->x_loc : canvas_ptr->x_loc \
	+ (canvas_ptr->y_loc - loc_int[1] + direct - 3) * ray_vec[0] / ray_vec[1];
	else
		hit_point = (ray_vec[0] == 0) ? canvas_ptr->y_loc : canvas_ptr->y_loc \
	+ (canvas_ptr->x_loc - loc_int[0] - direct) * ray_vec[1] / ray_vec[0];
	wall_info->wall_x = (int)((hit_point - floor(hit_point)) * \
			wall_info->wall_ptr->width);
}
