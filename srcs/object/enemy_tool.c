/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:15:11 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 10:15:13 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		enemy_gun_react(t_canvas *canvas_ptr, t_obj *enemy)
{
	if (enemy->health <= 0)
	{
		Mix_PlayChannel(-1, \
				search_sound(canvas_ptr->sounds, DIE_SOUND)->s, 0);
		enemy->pose = 36;
	}
	else
		Mix_PlayChannel(-1, \
				search_sound(canvas_ptr->sounds, HIT2_SOUND)->s, 0);
}

int			get_enemy_mv_idx(int theta)
{
	int				out;
	int				theta2;

	theta2 = theta * 2;
	out = -1;
	if (theta2 >= 360 - 45 && theta2 < 360 + 45)
		out = 0;
	else if (theta2 >= 270 - 45 && theta2 < 270 + 45)
		out = 1;
	else if (theta2 >= 180 - 45 && theta2 < 180 + 45)
		out = 2;
	else if (theta2 >= 90 - 45 && theta2 < 90 + 45)
		out = 3;
	else if (theta2 >= 720 - 45 || theta2 < 0 + 45)
		out = 4;
	else if (theta2 >= 630 - 45 && theta2 < 630 + 45)
		out = 5;
	else if (theta2 >= 540 - 45 && theta2 < 540 + 45)
		out = 6;
	else if (theta2 > 450 - 45 && theta2 < 450 + 45)
		out = 7;
	else
		printf("error\n");
	return (out);
}
