/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 01:45:26 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 18:21:54 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			in_game(t_canvas *canvas_ptr)
{
	int		my_state;

	enemies(canvas_ptr);
	my_state = check_status(canvas_ptr);
	if (my_state == 0)
	{
		movement(canvas_ptr);
		change_angle(canvas_ptr);
	}
	else if (my_state < 0)
		return (1);
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

int			load_next_round(t_canvas *canvas_ptr)
{
	static int		file_idx;
	char			*next_file_name;

	if (!file_idx)
		file_idx = 2;
	if (!(next_file_name = canvas_ptr->file_store[file_idx]))
		return (2);
	if ((init_next(canvas_ptr, next_file_name)))
		return (-print_error("wrong map"));
	file_idx++;
	return (0);
}

int			victory_loop(t_canvas *canvas_ptr, int game_state)
{
	if (game_state == 1)
		return (load_next_round(canvas_ptr));
	if (game_state == 2)
	{
		Mix_HaltChannel(RUN_SOUND);
		Mix_PlayMusic(canvas_ptr->bgm[BGM_VICTORY], 1);
		draw_full(canvas_ptr, search_img(canvas_ptr->imgs, VICTORY, 0));
	}
	mlx_put_image_to_window(canvas_ptr->mlx, canvas_ptr->window, \
			canvas_ptr->view, 0, 0);
	if (wait_ending(12000000) == 1)
		ending_writer(*canvas_ptr, "ESC TO END", STRING_COLOR1, 140);
	else if (wait_ending(9000000) == 1)
		ending_writer(*canvas_ptr, "THIS GAME", STRING_COLOR1, 140);
	else if (wait_ending(6000000) == 1)
		ending_writer(*canvas_ptr, "PLAYING", STRING_COLOR1, 140);
	else if (wait_ending(3000000) == 1)
		ending_writer(*canvas_ptr, "THANKS FOR", STRING_COLOR1, 140);
	else
		ending_writer(*canvas_ptr, "WELL DONE", STRING_COLOR1, 140);
	return (3);
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
			Mix_PlayMusic(canvas_ptr->bgm[BGM_ENDING], 1);
			game_state = -2;
		}
		if (wait_ending(7500000) == 1)
		{
			draw_full(canvas_ptr, search_img(canvas_ptr->imgs, ENDING, 0));
			mlx_put_image_to_window(canvas_ptr->mlx, canvas_ptr->window, \
					canvas_ptr->view, 0, 0);
			ending_writer(*canvas_ptr, "GAME OVER", STRING_COLOR1, 100);
		}
	}
	else
		game_state = victory_loop(canvas_ptr, game_state);
	return (0);
}

int			main(int argc, char *argv[])
{
	t_canvas	canvas;

	if (argc < 2)
		return (1);
	canvas.file_store = argv;
	if (init_all(&canvas, canvas.file_store[1]))
		return (3);
	if (argc == 3 && !strcmp(argv[2], "--save"))
	{
		if (save_bmp(&canvas))
			return (print_error("screen shot failed"));
	}
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
