/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:26:14 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 08:47:51 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			init_all(t_canvas *canvas_ptr, char *file_name)
{
	init_value(canvas_ptr);
	canvas_ptr->mlx = mlx_init();
	if (file_reader(canvas_ptr, file_name))
	{
		free_obj(canvas_ptr);
		free_img(canvas_ptr);
		return (1);
	}
	canvas_ptr->window = mlx_new_window(canvas_ptr->mlx, canvas_ptr->width, \
			canvas_ptr->height + canvas_ptr->hud_height, GAME_NAME);
	if (init_sound(canvas_ptr))
		return (1);
	if (init_canvas(canvas_ptr))
		return (1);
	if (init_hud(canvas_ptr))
		return (1);
	return (0);
}

int			init_next(t_canvas *canvas_ptr, char *file_name)
{
	free_obj(canvas_ptr);
	free_img(canvas_ptr);
	mlx_destroy_image(canvas_ptr->mlx, canvas_ptr->view);
	mlx_destroy_image(canvas_ptr->mlx, canvas_ptr->hud);
	mlx_destroy_window(canvas_ptr->mlx, canvas_ptr->window);
	free_map(&(canvas_ptr->map), canvas_ptr->map_col_size);
	if (file_reader(canvas_ptr, file_name))
	{
		free_obj(canvas_ptr);
		free_img(canvas_ptr);
		return (1);
	}
	canvas_ptr->window = mlx_new_window(canvas_ptr->mlx, canvas_ptr->width, \
			canvas_ptr->height + canvas_ptr->hud_height, GAME_NAME);
	if (init_canvas(canvas_ptr) || init_hud(canvas_ptr))
		return (1);
	mlx_hook(canvas_ptr->window, KEY_PRESS, 0, &key_press_hook, canvas_ptr);
	mlx_hook(canvas_ptr->window, KEY_RELEASE, 0, &key_release_hook, canvas_ptr);
	mlx_hook(canvas_ptr->window, MOUSE_PRESS, 0, &mouse_press_hook, canvas_ptr);
	mlx_hook(canvas_ptr->window, MOUSE_MOVE, 0, &mouse_move_hook, canvas_ptr);
	mlx_hook(canvas_ptr->window, MOUSE_RELEASE, 0, &mouse_release_hook, \
			canvas_ptr);
	mlx_hook(canvas_ptr->window, EXIT_KEY, 0, &close_hook, &canvas_ptr);
	return (0);
}
