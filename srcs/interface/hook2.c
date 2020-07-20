#include "cub3d.h"

void		gun_hook(t_canvas *canvas_ptr)
{
	t_obj		*target;

	if (!canvas_ptr->gun_fire && canvas_ptr->bullet_cnt)
	{
		Mix_PauseMusic();
		Mix_PlayChannel(-1, search_sound(canvas_ptr->sounds, FIRE_SOUND)->s, 0);
		canvas_ptr->gun_fire = GUN_MOTION_NUM;
		if (canvas_ptr->at_my_aim)
		{
			target = search_obj_id(canvas_ptr->objs, canvas_ptr->at_my_aim);
			if (target->label == ENEMY || target->label == BOSS)
			{
				Mix_PlayChannel(-1, search_sound(canvas_ptr->sounds, DIE_SOUND)->s, 0);
				target->pose = 36;
			}
			else if (target->label == TRAP)
				canvas_ptr->map[target->y_int][target->x_int] = 0;
		}
		canvas_ptr->bullet_cnt--;
		Mix_ResumeMusic();
	}
}
