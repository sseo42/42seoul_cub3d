/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo </var/mail/sseo>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 16:34:48 by sseo              #+#    #+#             */
/*   Updated: 2020/07/20 15:55:25 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			in_game(t_canvas *canvas_ptr)
{
	enemies(canvas_ptr);
	if (!(check_status(canvas_ptr)))
	{
		movement(canvas_ptr);
		change_angle(canvas_ptr);
	}
	animation(canvas_ptr);
	if (canvas_ptr->view_update)
		update_view(canvas_ptr);
	if (canvas_ptr->hud_update)
		update_hud(canvas_ptr);
	if (canvas_ptr->health > 0)
		return (0);
	else
		return (-1);
}
	
int			main_loop(t_canvas *canvas_ptr)
{
	static int		game_state;

	if (game_state == 0)
		game_state = in_game(canvas_ptr);
	else if (game_state < 0)
	{
		if (game_state == -1)
		{
			Mix_HaltChannel(RUN_SOUND);
			Mix_PlayMusic(canvas_ptr->bgm[4], 1);
			game_state = -2;
		}
		if (wait_ending(7500000) == 1)
		{
			draw_full(canvas_ptr, search_img(canvas_ptr->imgs, ENDING, 0));
			mlx_put_image_to_window(canvas_ptr->mlx, canvas_ptr->window, \
					canvas_ptr->view, 0, 0);
			ending_writer(*canvas_ptr, STRING_COLOR1);
		}
	}
	return (0);
}	

int			main(int argc, char *argv[])
{
	t_canvas	canvas;

	if (argc < 2 || argc > 3)
		return (1); //wrong arg
	if (init_all(&canvas, argv[1]))
		return (3); //map error
	if (argc == 3 && !(strcmp(argv[2], "--save")))
		printf("yet\n"); //save img
	else if (argc == 3)
		return (2); //wrong arg

	mlx_hook(canvas.window, KEY_PRESS, 0, &key_press_hook, &canvas);
	mlx_hook(canvas.window, KEY_RELEASE, 0, &key_release_hook, &canvas);
	mlx_hook(canvas.window, MOUSE_PRESS, 0, &mouse_press_hook, &canvas);
	mlx_hook(canvas.window, MOUSE_MOVE, 0, &mouse_move_hook, &canvas);
	mlx_hook(canvas.window, MOUSE_RELEASE, 0, &mouse_release_hook, &canvas);
	mlx_hook(canvas.window, EXIT_KEY, 0, &close_hook, &canvas);
	mlx_loop_hook(canvas.mlx, &main_loop, &canvas);
	mlx_loop(canvas.mlx);
	return (0);
}
