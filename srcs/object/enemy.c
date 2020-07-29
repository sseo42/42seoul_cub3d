/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 01:47:39 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 09:45:49 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				enemy_ray_to_me(t_canvas *canvas_ptr, \
				double enemy_ray[2], int enemy_x, int enemy_y)
{
	int				side;
	int				label;
	int				loc_int[4];
	double			distance[4];
	double			ray_vec[2];

	ray_vec[0] = -enemy_ray[0];
	ray_vec[1] = -enemy_ray[1];
	dda_init(canvas_ptr, ray_vec, loc_int, distance);
	while (1)
	{
		side = distance[0] < distance[1] ? 0 : 1;
		loc_int[side] += loc_int[side + 2];
		label = canvas_ptr->map[loc_int[1]][loc_int[0]];
		if (label == 1 || label == CLOSE_DOOR)
			break ;
		if (loc_int[0] == enemy_x && loc_int[1] == enemy_y)
			return (1);
		distance[side] += distance[side + 2];
	}
	return (0);
}

int				enemy_check_and_move(t_canvas *canvas_ptr, \
				t_obj *enemy, double dx, double dy)
{
	double			expect_x;
	double			expect_y;
	int				p_1;
	int				p_2;

	expect_x = enemy->x_loc + dx * ENEMY_MV_SPD;
	expect_y = enemy->y_loc - dy * ENEMY_MV_SPD;
	p_1 = (dy > 0) ? canvas_ptr->map[(int)(expect_y - 0.4)][(int)expect_x] \
				: canvas_ptr->map[(int)(expect_y + 0.4)][(int)expect_x];
	p_2 = (dx > 0) ? canvas_ptr->map[(int)expect_y][(int)(expect_x + 0.4)] \
				: canvas_ptr->map[(int)expect_y][(int)(expect_x - 0.4)];
	if (p_1 == WALL || p_1 == CLOSE_DOOR || p_2 == WALL || p_2 == CLOSE_DOOR)
		return (1);
	if (canvas_ptr->map[(int)expect_y][(int)expect_x] == 0 || \
			(enemy->x_int == (int)expect_x && enemy->y_int == (int)expect_y))
	{
		canvas_ptr->map[enemy->y_int][enemy->x_int] = 0;
		enemy->x_loc = expect_x;
		enemy->y_loc = expect_y;
		enemy->x_int = (int)expect_x;
		enemy->y_int = (int)expect_y;
		canvas_ptr->map[(int)expect_y][(int)expect_x] = enemy->label;
		return (0);
	}
	return (1);
}

void			enemy_movement(t_canvas *canvas_ptr, \
				t_obj *enemy, double enemy_ray[2], unsigned long current_time)
{
	double			dx;
	double			dy;

	dx = cos(enemy->angle * PI / 180);
	dy = sin(enemy->angle * PI / 180);
	if (enemy_ray_to_me(canvas_ptr, enemy_ray, enemy->x_int, enemy->y_int) && \
			(dx * enemy_ray[0] + dy * enemy_ray[1]) > ENEMY_VIEWING_ANGLE)
		enemy->pose = ENEMY_FIRE_MOTION_POSE;
	else
	{
		if ((enemy_check_and_move(canvas_ptr, enemy, dx, dy)))
		{
			enemy->angle = (enemy->angle + 90) % 360;
			enemy->pose = ((enemy->pose / 8) + 1) * 8 % ENEMY_MOVE_MOTION_NUM \
			+ get_enemy_mv_idx((360 + enemy->angle - canvas_ptr->angle) % 360);
		}
		if (current_time - enemy->last_clock > ENEMY_POSE_CLOCK)
		{
			enemy->last_clock = current_time;
			enemy->pose = ((enemy->pose / 8) + 1) * 8 % ENEMY_MOVE_MOTION_NUM \
			+ get_enemy_mv_idx((360 + enemy->angle - canvas_ptr->angle) % 360);
		}
	}
}

void			enemy_control(t_canvas *canvas_ptr, \
				t_obj *enemy, double enemy_ray[2])
{
	struct timespec	current;
	unsigned long	current_time;

	clock_gettime(CLOCK_MONOTONIC, &current);
	current_time = get_ms(current);
	if (enemy->pose >= ENEMY_DIE_MOTION_POSE && \
			current_time - enemy->last_clock > ENEMY_DIE_POSE_CLOCK)
	{
		enemy_die_animation(canvas_ptr, enemy, current_time);
	}
	else if (enemy->pose >= ENEMY_FIRE_MOTION_POSE && \
			enemy->pose < ENEMY_DIE_MOTION_POSE && \
			current_time - enemy->last_clock > ENEMY_ATK_SPD)
	{
		enemy_fire_animation(canvas_ptr, enemy, enemy_ray, current_time);
	}
	else if (enemy->pose < ENEMY_FIRE_MOTION_POSE)
		enemy_movement(canvas_ptr, enemy, enemy_ray, current_time);
}

void			enemies(t_canvas *canvas_ptr)
{
	t_obj			*enemy;
	double			enemy_ray[2];
	double			ray_scale;

	enemy = canvas_ptr->objs;
	while (enemy)
	{
		if (enemy->label == ENEMY || enemy->label == BOSS)
		{
			enemy_ray[0] = canvas_ptr->x_loc - enemy->x_loc;
			enemy_ray[1] = enemy->y_loc - canvas_ptr->y_loc;
			ray_scale = sqrt(pow(enemy_ray[0], 2) + pow(enemy_ray[1], 2));
			enemy_ray[0] /= ray_scale;
			enemy_ray[1] /= ray_scale;
			enemy_control(canvas_ptr, enemy, enemy_ray);
			if (enemy_ray[0] * cos(canvas_ptr->angle * PI / 180) + \
				enemy_ray[1] * sin(canvas_ptr->angle * PI / 180) < 0)
				canvas_ptr->view_update = 1;
		}
		enemy = enemy->next;
	}
}
