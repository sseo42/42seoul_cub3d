/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:47:18 by sseo              #+#    #+#             */
/*   Updated: 2020/07/20 14:28:42 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_aim(t_canvas *canvas_ptr)
{
	int		x_loc;
	int		y_loc;
	int		i;

	x_loc = canvas_ptr->width / 2;
	y_loc = canvas_ptr->height / 2;
	i = -AIM_SIZE;
	while (i < AIM_SIZE + 1)
	{
		canvas_ptr->view_buf[y_loc * canvas_ptr->width + x_loc + i] = AIM_COLOR;
		canvas_ptr->view_buf[(y_loc + i) * canvas_ptr->width + x_loc] = AIM_COLOR;
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
	int		total_width;
	int		total_height;
	int		w;
	int		h;

	total_width = (canvas_ptr->width > canvas_ptr->hud_width) ? \
				  canvas_ptr->width : canvas_ptr->hud_width;
	total_height = canvas_ptr->height + canvas_ptr->hud_height;
	mlx_destroy_image(canvas_ptr->mlx, canvas_ptr->view);
	canvas_ptr->view = mlx_new_image(canvas_ptr->mlx, total_width, total_height);
	canvas_ptr->view_data = (int *)mlx_get_data_addr(canvas_ptr->view, \
			&(canvas_ptr->bpp), &(canvas_ptr->sl), &(canvas_ptr->endian));
	w = 0;
	while (w < total_width)
	{
		h = 0;
		while (h < total_height)
		{
			canvas_ptr->view_data[h * canvas_ptr->sl / 4 + w] = \
				img_ptr->data[(h * img_ptr->height / total_height) * \
					img_ptr->sl / 4 + (w * img_ptr->width / total_width)];
			h++;
		}
		w++;
	}
}
