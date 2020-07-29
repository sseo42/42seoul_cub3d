/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 02:01:29 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 18:30:10 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ending_writer(t_canvas canvas, char *word, \
			int color, int size_ratio)
{
	char	string_size[2];
	char	*ending;

	string_size[0] = (char)(canvas.width / size_ratio);
	string_size[1] = 0;
	ending = ft_strjoin((const char *)string_size, (const char *)word);
	mlx_string_put(canvas.mlx, canvas.window, canvas.width / 2 - \
			(int)(*ending * 45), canvas.height * 3 / 4, color, ending);
	free(ending);
}

void		health_writer(t_canvas canvas, int x_loc, int y_loc, int color)
{
	char	hp_str[5];

	hp_str[0] = (char)(canvas.hud_height / 20);
	if (hp_str[0] == 0)
		hp_str[0] = 1;
	if (canvas.health == 100)
	{
		hp_str[1] = '1';
		hp_str[2] = '0';
		hp_str[3] = '0';
		hp_str[4] = 0;
	}
	else
	{
		hp_str[1] = canvas.health / 10 + '0';
		hp_str[2] = canvas.health % 10 + '0';
		hp_str[3] = 0;
	}
	mlx_string_put(canvas.mlx, canvas.window, x_loc - (int)hp_str[0] * 10, \
			y_loc + (int)hp_str[0] * 3, color, hp_str);
}

void		bullet_writer(t_canvas canvas)
{
	char	bullet_cnt[4];

	bullet_cnt[0] = canvas.width / 400;
	if (bullet_cnt[0] == 0)
		bullet_cnt[0] = 1;
	bullet_cnt[1] = canvas.bullet_cnt / 10 + '0';
	bullet_cnt[2] = canvas.bullet_cnt % 10 + '0';
	bullet_cnt[3] = 0;
	mlx_string_put(canvas.mlx, canvas.window, 0, \
			bullet_cnt[0] * 10, STRING_COLOR1, bullet_cnt);
}

void		hud_render(t_canvas *canvas_ptr)
{
	int		h;
	int		w;
	int		w_max;
	int		h_width;

	h = 0;
	w_max = canvas_ptr->hud_width * canvas_ptr->health / INITIAL_HP;
	while (h < canvas_ptr->hud_height)
	{
		w = 0;
		h_width = h * canvas_ptr->hud_width;
		while (w < canvas_ptr->hud_width)
		{
			if (w > w_max)
				canvas_ptr->hud_buf[h_width + w] = 0;
			else
				canvas_ptr->hud_buf[h_width + w] = HUD_COLOR;
			w++;
		}
		h++;
	}
}

void		update_hud(t_canvas *canvas_ptr)
{
	int		h;
	int		w;
	int		h_sl;
	int		h_width;

	h = 0;
	hud_render(canvas_ptr);
	while (h < canvas_ptr->hud_height)
	{
		w = 0;
		h_sl = h * canvas_ptr->hud_sl / 4;
		h_width = h * canvas_ptr->hud_width;
		while (w < canvas_ptr->hud_width)
		{
			canvas_ptr->hud_data[h_sl + w] = canvas_ptr->hud_buf[h_width + w];
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(canvas_ptr->mlx, canvas_ptr->window, \
			canvas_ptr->hud, 0, canvas_ptr->height);
	health_writer(*canvas_ptr, canvas_ptr->hud_width / 2, \
			canvas_ptr->height + canvas_ptr->hud_height / 2, STRING_COLOR1);
	canvas_ptr->hud_update = 0;
}
