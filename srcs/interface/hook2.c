/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 01:41:50 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 09:44:55 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		gun_hook(t_canvas *canvas_ptr)
{
	t_obj		*target;

	if (!canvas_ptr->gun_fire && canvas_ptr->bullet_cnt)
	{
		Mix_PlayChannel(-1, search_sound(canvas_ptr->sounds, FIRE_SOUND)->s, 0);
		canvas_ptr->gun_fire = GUN_MOTION_NUM;
		if (canvas_ptr->at_my_aim)
		{
			target = search_obj_id(canvas_ptr->objs, canvas_ptr->at_my_aim);
			if (target->label == ENEMY || target->label == BOSS)
			{
				target->health -= GUN_DMG;
				enemy_gun_react(canvas_ptr, target);
			}
			else if (target->label == TRAP)
				canvas_ptr->map[target->y_int][target->x_int] = 0;
		}
		canvas_ptr->bullet_cnt--;
	}
}
