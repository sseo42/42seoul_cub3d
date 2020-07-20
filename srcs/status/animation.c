#include "cub3d.h"

void		jump_animation(t_canvas *canvas_ptr)
{
	canvas_ptr->horizon_line += canvas_ptr->jump_state;
	if (canvas_ptr->jump_state > 0)
	{
		canvas_ptr->jump_state--;
		if (!canvas_ptr->jump_state)
			canvas_ptr->jump_state = -JUMP_HEIGHT;
	}
	else
		canvas_ptr->jump_state++;
}

void		gun_animation(t_canvas *canvas_ptr)
{
	canvas_ptr->gun_fire--;
	canvas_ptr->horizon_line += canvas_ptr->gun_fire * canvas_ptr->gun_fire * canvas_ptr->height / 200;
}

void		animation(t_canvas *canvas_ptr)
{
	if (canvas_ptr->jump_state)
	{
		jump_animation(canvas_ptr);
		canvas_ptr->view_update = 1;
	}
	if (canvas_ptr->gun_fire)
	{
		gun_animation(canvas_ptr);
		canvas_ptr->view_update = 1;
	}
}

void		enemy_die_animation(t_canvas *canvas_ptr, t_obj *enemy, unsigned long current_time)
{
	enemy->last_clock = current_time;
	if (enemy_pose < ENEMY_DIE_MOTION_POSE + ENEMY_DIE_MOTION_NUM)
		enemy_pose++;
	else
	{
		enemy_label = (enemy->label == ENEMY) ? DEAD_ENEMY : DEAD_BOSS;
		canvas_ptr->map[enemy->y_int][enemy->x_int] = enemy->label;
	}
}

void		enemy_fire_animation(t_canvas *canvas_ptr, t_obj *enemy, double enemy_ray[2], unsigned long current_time)
{
	enemy->last_clock = current_time;
	if (enemy->pose == ENEMY_FIRE_MOTION_POSE + ENEMY_FIRE_MOTION_NUM)
	{
		enemy->pose = 0;
		if (enemy_ray_to_me(canvas_ptr, enemy_ray, \
					enemy->x_int, enemy->y_int))
			canvas_ptr->hit_dmg += (enemy->label == ENEMY) ? \
								   ENEMY_DMG : BOSS_DMG;
	}
	else
		enemy->pose++;
}
