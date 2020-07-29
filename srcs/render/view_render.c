/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 02:03:31 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 12:14:24 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		bg_wall_render(t_canvas *canvas_ptr, t_wall_info *wall_info, \
			double ray_vec[2], int w)
{
	t_img		*wall_ptr;
	t_img		*ceiling_ptr;
	t_img		*floor_ptr;
	int			h_idx;
	int			color;

	wall_ptr = wall_info->wall_ptr;
	ceiling_ptr = search_img(canvas_ptr->imgs, WALL, UP);
	floor_ptr = search_img(canvas_ptr->imgs, WALL, DOWN);
	h_idx = 0;
	while (++h_idx < canvas_ptr->height)
	{
		if (h_idx >= wall_info->draw_start && h_idx < wall_info->draw_end)
			color = get_shade(wall_ptr->data[(h_idx - wall_info->draw_start) * \
				wall_ptr->height / wall_info->line_height * wall_ptr->sl / \
				4 + wall_info->wall_x], wall_info->distance * SHADE_INTENSITY);
		else
		{
			if (h_idx < canvas_ptr->horizon_line)
				color = get_bg_color(canvas_ptr, ceiling_ptr, ray_vec, h_idx);
			else
				color = get_bg_color(canvas_ptr, floor_ptr, ray_vec, h_idx);
		}
		canvas_ptr->view_buf[h_idx * canvas_ptr->width + w] = color;
	}
}

void		objs_render(t_canvas *canvas_ptr, t_obj_info **obj_info, \
			double angle_vec[2])
{
	t_img		*obj_img;
	t_obj_info	*target;
	int			render_info[5];

	sort_obj_info(obj_info);
	target = *obj_info;
	while (target)
	{
		if (!(obj_img = search_img(canvas_ptr->imgs, target->label, \
						target->pose)))
		{
			print_error("no image!!");
			exit(1);
		}
		get_obj_render_info(canvas_ptr, target, angle_vec, render_info);
		objs_render_loop(canvas_ptr, target, obj_img, render_info);
		target = target->next;
	}
	free_obj_info(obj_info);
}

int			view_render(t_canvas *canvas_ptr)
{
	t_wall_info			*wall_info;
	t_obj_info			*obj_info;
	int					w;
	double				angle_vec[2];
	double				ray_vec[2];

	if (!(wall_info = (t_wall_info *)malloc(sizeof(t_wall_info))))
		exit(1);
	obj_info = 0;
	w = -1;
	angle_vec[0] = cos((double)canvas_ptr->angle * PI / 180);
	angle_vec[1] = sin((double)canvas_ptr->angle * PI / 180);
	while (++w < canvas_ptr->width)
	{
		ray_vec[0] = angle_vec[0] + angle_vec[1] * (2 * w - canvas_ptr->width) \
						* canvas_ptr->plane_vec_scale / canvas_ptr->width;
		ray_vec[1] = angle_vec[1] - angle_vec[0] * (2 * w - canvas_ptr->width) \
						* canvas_ptr->plane_vec_scale / canvas_ptr->width;
		dda(canvas_ptr, wall_info, &obj_info, ray_vec);
		update_obj_info(obj_info, wall_info, w, angle_vec);
		bg_wall_render(canvas_ptr, wall_info, ray_vec, w);
	}
	objs_render(canvas_ptr, &obj_info, angle_vec);
	free(wall_info);
	return (0);
}

void		option_render(t_canvas *canvas_ptr)
{
	draw_aim(canvas_ptr);
	draw_gun(canvas_ptr);
	if (canvas_ptr->hit_state)
		insert_filter(canvas_ptr, 50, 0, 0);
}

void		update_view(t_canvas *canvas_ptr)
{
	int		h;
	int		w;
	int		h_sl;
	int		h_width;

	h = -1;
	canvas_ptr->at_my_aim = 0;
	view_render(canvas_ptr);
	if (EXTEND_VERSION)
		option_render(canvas_ptr);
	while (++h < canvas_ptr->height)
	{
		w = -1;
		h_sl = h * canvas_ptr->sl / 4;
		h_width = h * canvas_ptr->width;
		while (++w < canvas_ptr->width)
		{
			canvas_ptr->view_data[h_sl + w] = canvas_ptr->view_buf[h_width + w];
		}
	}
	mlx_put_image_to_window(canvas_ptr->mlx, canvas_ptr->window, \
			canvas_ptr->view, 0, 0);
	bullet_writer(*canvas_ptr);
	canvas_ptr->view_update = 0;
}
