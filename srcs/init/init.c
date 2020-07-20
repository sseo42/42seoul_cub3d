/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:26:14 by sseo              #+#    #+#             */
/*   Updated: 2020/07/20 18:15:02 by sseo             ###   ########.fr       */
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
}

int			init_sound(t_canvas *canvas_ptr)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return (print_error(SDL_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (print_error(SDL_GetError()));
	canvas_ptr->bgm[0] = Mix_LoadMUS("./SFX/Dark_Halls.mp3");
	canvas_ptr->bgm[4] = Mix_LoadMUS("./SFX/Ending.mp3");
	if (canvas_ptr->bgm[0] == NULL || canvas_ptr->bgm[4] == NULL)
		return (print_error(SDL_GetError()));
	if (add_sound(canvas_ptr, "./SFX/gun.wav", FIRE_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/run.wav", RUN_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/die1.wav", DIE_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/hit.wav", HIT_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/potion.wav", POTION_SOUND))
		return (1);
	if (add_sound(canvas_ptr, "./SFX/reload.wav", RELOAD_SOUND))
		return (1);
	if (Mix_PlayChannel(RUN_SOUND, search_sound(canvas_ptr->sounds, RUN_SOUND)->s, 0) < 0)
		return (print_error(SDL_GetError()));
	if (Mix_PlayMusic(canvas_ptr->bgm[0], -1) < 0)
		return (print_error(SDL_GetError()));
	return (0);
}

int			init_hud(t_canvas *canvas_ptr)
{
	canvas_ptr->hud = mlx_new_image(canvas_ptr->mlx, canvas_ptr->hud_width, \
			canvas_ptr->hud_height);
	canvas_ptr->hud_data = (int *)mlx_get_data_addr(canvas_ptr->hud, \
			&canvas_ptr->hud_bpp, &canvas_ptr->hud_sl, &canvas_ptr->hud_endian);
	canvas_ptr->hud_buf = (int *)malloc(sizeof(int) * canvas_ptr->hud_width * canvas_ptr->hud_height);
	canvas_ptr->hud_update = 1;
	if (canvas_ptr->hud_buf == NULL)
		return (print_error(strerror(errno)));
	return (0);
}

int			init_canvas(t_canvas *canvas_ptr)
{
	canvas_ptr->view = mlx_new_image(canvas_ptr->mlx, canvas_ptr->width, \
		   canvas_ptr->height);
	canvas_ptr->view_data = (int *)mlx_get_data_addr(canvas_ptr->view, \
			&canvas_ptr->bpp, &canvas_ptr->sl, &canvas_ptr->endian);
	canvas_ptr->view_buf = (int *)malloc(sizeof(int) * canvas_ptr->width * \
			canvas_ptr->height);
	canvas_ptr->view_update = 1;
	if (canvas_ptr->view_buf == NULL)
		return (print_error(strerror(errno)));
	return (0);
}

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
