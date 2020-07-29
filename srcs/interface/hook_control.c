/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 01:42:34 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 08:45:04 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_press_hook(int keycode, t_canvas *canvas_ptr)
{
	if (keycode == ESC_KEY)
		close_hook(canvas_ptr);
	else if (keycode == CLEAN_KEY)
		mlx_clear_window(canvas_ptr->mlx, canvas_ptr->window);
	else if (keycode == WEST_KEY || keycode == EAST_KEY || \
			keycode == NORTH_KEY || keycode == SOUTH_KEY)
		move_hook(keycode, canvas_ptr, 1);
	else if (keycode >= LEFT_KEY && keycode <= UP_KEY)
		angle_hook(keycode, canvas_ptr, 1);
	else if (keycode == JUMP_KEY)
		jump_hook(keycode, canvas_ptr);
	else if (keycode == DOOR_KEY)
		door_hook(canvas_ptr);
	else if (keycode == FIRE_KEY && EXTEND_VERSION)
		gun_hook(canvas_ptr);
	else
		printf("yet\n");
	return (0);
}

int			key_release_hook(int keycode, t_canvas *canvas_ptr)
{
	if (keycode == WEST_KEY || keycode == EAST_KEY || \
			keycode == NORTH_KEY || keycode == SOUTH_KEY)
		move_hook(keycode, canvas_ptr, 0);
	else if (keycode >= LEFT_KEY && keycode <= UP_KEY)
		angle_hook(keycode, canvas_ptr, 0);
	return (0);
}

int			mouse_press_hook(int button, int x, int y, t_canvas *canvas_ptr)
{
	if (button == 1)
	{
		canvas_ptr->mouse_on = 1;
		canvas_ptr->mouse_x = x;
		canvas_ptr->mouse_y = y;
	}
	else
		gun_hook(canvas_ptr);
	return (0);
}

int			mouse_release_hook(int button, int x, int y, t_canvas *canvas_ptr)
{
	if (button == 1)
	{
		canvas_ptr->mouse_on = 0;
		canvas_ptr->mouse_x = x;
		canvas_ptr->mouse_y = y;
	}
	return (0);
}

int			mouse_move_hook(int x, int y, t_canvas *canvas_ptr)
{
	int				dx;
	int				dy;
	static int		last_x;
	static int		last_y;

	if ((last_x == 0 && last_y == 0) && canvas_ptr->mouse_on)
	{
		last_x = canvas_ptr->mouse_x;
		last_y = canvas_ptr->mouse_y;
	}
	if (canvas_ptr->mouse_on)
	{
		dx = x - last_x;
		dy = y - last_y;
		last_x = x;
		last_y = y;
		canvas_ptr->tilting_spd = -dy * MOUSE_SENSITY * TILTING_SPD / 100;
		canvas_ptr->rot_spd = -dx * MOUSE_SENSITY * ROT_SPD / 100;
	}
	else
	{
		last_x = 0;
		last_y = 0;
	}
	return (0);
}
