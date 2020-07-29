/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:02:19 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 08:39:07 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_value(t_canvas *canvas_ptr)
{
	canvas_ptr->plane_vec_scale = tan(VIEWING_ANGLE * PI / 360);
	canvas_ptr->horizon_mv_info = 0;
	canvas_ptr->vertical_mv_info = 0;
	canvas_ptr->rot_spd = 0;
	canvas_ptr->tilting_spd = 0;
	canvas_ptr->mouse_on = 0;
	canvas_ptr->mouse_x = 0;
	canvas_ptr->mouse_y = 0;
	canvas_ptr->jump_state = 0;
	canvas_ptr->gun_fire = 0;
	canvas_ptr->hit_state = 0;
	canvas_ptr->health = INITIAL_HP;
	canvas_ptr->at_my_aim = 0;
	canvas_ptr->hit_dmg = 0;
	canvas_ptr->bullet_cnt = BULLET_INIT_CNT;
	canvas_ptr->objs = 0;
	canvas_ptr->imgs = 0;
	canvas_ptr->view_buf = 0;
	canvas_ptr->hud_buf = 0;
}

int			init_effect_sound(t_canvas *canvas_ptr)
{
	if (add_sound(canvas_ptr, "./SFX/gun.wav", FIRE_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/run.wav", RUN_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/die1.wav", DIE_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/hit.wav", HIT_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/hit2.wav", HIT2_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/potion.wav", POTION_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/reload.wav", RELOAD_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/door.wav", DOOR_SOUND))
		return (1);
	return (0);
}

int			init_sound(t_canvas *canvas_ptr)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return (print_error(SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0)
		return (print_error(SDL_GetError()));
	canvas_ptr->bgm[BGM_BASIC] = Mix_LoadMUS("./SFX/Dark_Halls.mp3");
	canvas_ptr->bgm[BGM_RUSH] = Mix_LoadMUS("./SFX/eyes_of_the_tiger.mp3");
	canvas_ptr->bgm[BGM_VICTORY] = Mix_LoadMUS("./SFX/GFN.mp3");
	canvas_ptr->bgm[BGM_ENDING] = Mix_LoadMUS("./SFX/Ending.mp3");
	if (canvas_ptr->bgm[BGM_BASIC] == 0 || canvas_ptr->bgm[BGM_RUSH] == 0 || \
		canvas_ptr->bgm[BGM_VICTORY] == 0 || canvas_ptr->bgm[BGM_ENDING] == 0)
		return (print_error(SDL_GetError()));
	init_effect_sound(canvas_ptr);
	if (Mix_PlayChannel(RUN_SOUND, \
				search_sound(canvas_ptr->sounds, RUN_SOUND)->s, 0) < 0)
		return (print_error(SDL_GetError()));
	if (Mix_PlayMusic(canvas_ptr->bgm[BGM_BASIC], -1) < 0)
		return (print_error(SDL_GetError()));
	return (0);
}

int			init_hud(t_canvas *canvas_ptr)
{
	free(canvas_ptr->hud_buf);
	canvas_ptr->hud_buf = 0;
	canvas_ptr->hud = mlx_new_image(canvas_ptr->mlx, canvas_ptr->hud_width, \
						canvas_ptr->hud_height);
	canvas_ptr->hud_data = (int *)mlx_get_data_addr(canvas_ptr->hud, \
							&canvas_ptr->hud_bpp, &canvas_ptr->hud_sl, \
							&canvas_ptr->hud_endian);
	canvas_ptr->hud_buf = (int *)malloc(sizeof(int) * \
							canvas_ptr->hud_width * canvas_ptr->hud_height);
	canvas_ptr->hud_update = 1;
	if (canvas_ptr->hud_buf == NULL)
		return (print_error(strerror(errno)));
	return (0);
}

int			init_canvas(t_canvas *canvas_ptr)
{
	free(canvas_ptr->view_buf);
	canvas_ptr->view_buf = 0;
	canvas_ptr->view = mlx_new_image(canvas_ptr->mlx, canvas_ptr->width, \
						canvas_ptr->height);
	canvas_ptr->view_data = (int *)mlx_get_data_addr(canvas_ptr->view, \
			&canvas_ptr->bpp, &canvas_ptr->sl, &canvas_ptr->endian);
	canvas_ptr->view_buf = (int *)malloc(sizeof(int) * canvas_ptr->width * \
			canvas_ptr->height);
	canvas_ptr->view_update = 1;
	if (canvas_ptr->view_buf == NULL)
		return (print_error(strerror(errno)));
	if (EXTEND_VERSION)
	{
		if (add_xpm_img(canvas_ptr, "./textures/shotgun1.xpm", 0, 0))
			return (1);
		if (add_xpm_img(canvas_ptr, "./textures/shotgun5.xpm", 0, 1))
			return (1);
		if (add_xpm_img(canvas_ptr, "./textures/shotgun4.xpm", 0, 2))
			return (1);
		if (add_xpm_img(canvas_ptr, "./textures/shotgun3.xpm", 0, 3))
			return (1);
		if (add_xpm_img(canvas_ptr, "./textures/shotgun2.xpm", 0, 4))
			return (1);
	}
	return (0);
}
