/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:47:18 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 18:26:04 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_aim(t_canvas *canvas_ptr)
{
	int		x_loc;
	int		y_loc;
	int		range;
	int		i;

	x_loc = canvas_ptr->width / 2;
	y_loc = canvas_ptr->height / 2;
	range = (x_loc > y_loc) ? y_loc * AIM_SIZE / 500 : x_loc * AIM_SIZE / 500;
	i = -range;
	while (i < range + 1)
	{
		canvas_ptr->view_buf[y_loc * canvas_ptr->width + x_loc + i] = AIM_COLOR;
		canvas_ptr->view_buf[(y_loc + i) * canvas_ptr->width + x_loc] = \
																	AIM_COLOR;
		i++;
	}
}

void		draw_gun(t_canvas *canvas_ptr)
{
	t_img	*gun_img;
	int		w;
	int		h;
	int		color;

	gun_img = search_img(canvas_ptr->imgs, 0, canvas_ptr->gun_fire);
	w = 0;
	while (w < canvas_ptr->width)
	{
		h = 0;
		while (h < canvas_ptr->height)
		{
			color = gun_img->data[(h * gun_img->height / canvas_ptr->height) * \
					gun_img->sl / 4 + (w * gun_img->width / canvas_ptr->width)];
			if (color != gun_img->bg_color)
				canvas_ptr->view_buf[h * canvas_ptr->width + w] = color;
			h++;
		}
		w++;
	}
}

void		draw_full(t_canvas *canvas_ptr, t_img *img_ptr)
{
	int		full_width;
	int		full_height;
	int		w;
	int		h;

	full_width = (canvas_ptr->width > canvas_ptr->hud_width) ? \
					canvas_ptr->width : canvas_ptr->hud_width;
	full_height = canvas_ptr->height + canvas_ptr->hud_height;
	mlx_destroy_image(canvas_ptr->mlx, canvas_ptr->view);
	canvas_ptr->view = mlx_new_image(canvas_ptr->mlx, full_width, full_height);
	canvas_ptr->view_data = (int *)mlx_get_data_addr(canvas_ptr->view, \
			&(canvas_ptr->bpp), &(canvas_ptr->sl), &(canvas_ptr->endian));
	w = 0;
	while (w < full_width)
	{
		h = 0;
		while (h < full_height)
		{
			canvas_ptr->view_data[h * canvas_ptr->sl / 4 + w] = \
				img_ptr->data[(h * img_ptr->height / full_height) * \
					img_ptr->sl / 4 + (w * img_ptr->width / full_width)];
			h++;
		}
		w++;
	}
}
