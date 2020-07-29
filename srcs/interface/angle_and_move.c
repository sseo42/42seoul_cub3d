/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_and_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 01:37:14 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 01:43:01 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		change_angle(t_canvas *canvas_ptr)
{
	if (canvas_ptr->rot_spd)
	{
		canvas_ptr->angle = (canvas_ptr->angle + canvas_ptr->rot_spd) % 360;
		if (canvas_ptr->mouse_on)
			canvas_ptr->rot_spd = 0;
		canvas_ptr->view_update = 1;
	}
	if (canvas_ptr->tilting_spd)
	{
		canvas_ptr->horizon_line += canvas_ptr->tilting_spd;
		if (canvas_ptr->mouse_on)
			canvas_ptr->tilting_spd = 0;
		if (canvas_ptr->horizon_line < 0)
			canvas_ptr->horizon_line = 0;
		else if (canvas_ptr->horizon_line > canvas_ptr->height)
			canvas_ptr->horizon_line = canvas_ptr->height;
		canvas_ptr->view_update = 1;
	}
}

void		check_and_move(t_canvas *canvas_ptr, double cos_val, double sin_val)
{
	double	x_pos;
	double	y_pos;
	int		check1;
	int		check2;

	x_pos = canvas_ptr->x_loc + cos_val;
	y_pos = canvas_ptr->y_loc - sin_val;
	if (cos_val < 0)
		check1 = canvas_ptr->map[(int)y_pos][(int)(x_pos - 0.01)];
	else
		check1 = canvas_ptr->map[(int)y_pos][(int)(x_pos + 0.01)];
	if (sin_val < 0)
		check2 = canvas_ptr->map[(int)(y_pos + 0.01)][(int)x_pos];
	else
		check2 = canvas_ptr->map[(int)(y_pos - 0.01)][(int)x_pos];
	if ((check1 == 0 || check1 > 5) && (check2 == 0 || check2 > 5))
	{
		canvas_ptr->x_loc = x_pos;
		canvas_ptr->y_loc = y_pos;
		canvas_ptr->view_update = 1;
	}
}

int			movement(t_canvas *canvas_ptr)
{
	int		direction;

	if (canvas_ptr->horizon_mv_info == 1 || canvas_ptr->horizon_mv_info == 2)
	{
		direction = canvas_ptr->angle + 90 * \
					(3 - canvas_ptr->horizon_mv_info * 2);
		if (canvas_ptr->vertical_mv_info == 1 || \
				canvas_ptr->vertical_mv_info == 2)
			direction += 45 * (canvas_ptr->vertical_mv_info * 2 - 3) * \
							(3 - canvas_ptr->horizon_mv_info * 2);
	}
	else if (canvas_ptr->vertical_mv_info == 1 || \
			canvas_ptr->vertical_mv_info == 2)
		direction = canvas_ptr->angle + 180 * \
					(canvas_ptr->vertical_mv_info - 1);
	else
	{
		Mix_Pause(RUN_SOUND);
		return (0);
	}
	Mix_Resume(RUN_SOUND);
	check_and_move(canvas_ptr, MV_SPD * cos(direction * PI / 180), \
			MV_SPD * sin(direction * PI / 180));
	return (0);
}
