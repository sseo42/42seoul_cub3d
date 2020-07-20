#include "cub3d.h"

void		eye(t_canvas *canvas_ptr, int info[3])
{
	info[0] = (int)(canvas_ptr->x_loc + cos(canvas_ptr->angle * PI / 180));
	info[1] = (int)(canvas_ptr->y_loc - sin(canvas_ptr->angle * PI / 180));
	info[2] = canvas_ptr->map[info[1]][info[0]];
}

void		potion_react(t_canvas *canvas_ptr)
{
		Mix_PlayChannel(-1, search_sound(canvas_ptr->sounds, POTION_SOUND)->s, 0);
		canvas_ptr->health -= canvas_ptr->hit_dmg;
		canvas_ptr->hit_dmg = 0;
		canvas_ptr->hud_update = 1;
}

void		dmg_react(t_canvas *canvas_ptr)
{
	struct timespec			current;
	static unsigned long	start_time;
	unsigned long			current_time;

	if (canvas_ptr->hit_dmg > 0)
	{
		Mix_PlayChannel(-1, search_sound(canvas_ptr->sounds, HIT_SOUND)->s, 0);
		canvas_ptr->health -= canvas_ptr->hit_dmg;
		canvas_ptr->hit_dmg = 0;
		canvas_ptr->hit_state = 1;
		canvas_ptr->hud_update = 1;
		clock_gettime(CLOCK_MONOTONIC, &current);
		start_time = get_ms(current);
	}
	if (start_time)
	{
		clock_gettime(CLOCK_MONOTONIC, &current);
		current_time = get_ms(current);
		if (current_time - start_time > HIT_PAUSE)
		{
			canvas_ptr->hit_state = 0;
			start_time = 0;
		}
		canvas_ptr->view_update = 1;
	}
}

void		check_my_loc(t_canvas *canvas_ptr)
{
	int						x_int;
	int						y_int;
	int						item;

	x_int = (int)canvas_ptr->x_loc;
	y_int = (int)canvas_ptr->y_loc;
	item = canvas_ptr->map[y_int][x_int];
	if (item == TRAP)
	{
		canvas_ptr->map[y_int][x_int] = 0;
		canvas_ptr->hit_dmg += TRAP_DMG;
	}
	else if (item == POTION)
	{
		canvas_ptr->map[y_int][x_int] = 0;
		canvas_ptr->hit_dmg -= POTION_DMG;
	}
	else if (item == BULLET)
	{
		Mix_PlayChannel(-1, search_sound(canvas_ptr->sounds, RELOAD_SOUND)->s, 0);
		canvas_ptr->map[y_int][x_int] = 0;
		canvas_ptr->bullet_cnt += 10;
		canvas_ptr->view_update = 1;
	}
}

int			check_status(t_canvas *canvas_ptr)
{
	check_my_loc(canvas_ptr);
	if (canvas_ptr->hit_dmg >= 0)
		dmg_react(canvas_ptr);
	else
		potion_react(canvas_ptr);
	if (canvas_ptr->health > 100)
		canvas_ptr->health = 100;
	if (canvas_ptr->health < 0)
		canvas_ptr->health = 0;
	return (canvas_ptr->hit_state);
}
