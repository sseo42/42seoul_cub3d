/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:51:36 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 18:59:11 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define EXTEND_VERSION 1
# define GAME_NAME "test_game"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <limits.h>
# include <string.h>
# include <time.h>
# include "mlx.h"
# include "render.h"
# include "interface.h"
# include "img.h"
# include "obj.h"
# include "sound.h"
# include "mode.h"
# include "get_next_line.h"
# include "init.h"

typedef struct	s_canvas
{
	char		**file_store;
	void		*mlx;
	void		*window;
	int			**map;
	int			map_col_size;
	void		*view;
	int			*view_data;
	int			width;
	int			height;
	int			bpp;
	int			sl;
	int			endian;
	int			*view_buf;
	int			view_update;
	double		x_loc;
	double		y_loc;
	int			angle;
	int			horizon_line;
	double		plane_vec_scale;
	int			horizon_mv_info;
	int			vertical_mv_info;
	int			rot_spd;
	int			tilting_spd;
	int			mouse_on;
	int			mouse_x;
	int			mouse_y;
	int			jump_state;
	int			gun_fire;
	int			hit_state;
	void		*hud;
	int			*hud_data;
	int			hud_width;
	int			hud_height;
	int			hud_bpp;
	int			hud_sl;
	int			hud_endian;
	int			*hud_buf;
	int			hud_update;
	int			health;
	int			at_my_aim;
	int			hit_dmg;
	int			bullet_cnt;
	t_obj		*objs;
	t_img		*imgs;
	Mix_Music	*bgm[5];
	t_sound		*sounds;
}				t_canvas;

/*
**	main.c
*/
int				in_game(t_canvas *canvas_ptr);
int				main_loop(t_canvas *canvas_ptr);

/*
**	init.c
*/
int				init_all(t_canvas *canvas_ptr, char *file_name);
int				init_next(t_canvas *canvas_ptr, char *file_name);

/*
**	init_tool.c
*/
void			init_value(t_canvas *canvas_ptr);
int				init_effect_sound(t_canvas *canvas_ptr);
int				init_sound(t_canvas *canvas_ptr);
int				init_canvas(t_canvas *canvas_ptr);
int				init_hud(t_canvas *canvas_ptr);

/*
**	reader.c
*/
int				get_path_info(t_canvas *canvas_ptr, const char *line);
int				file_reader(t_canvas *canvas_ptr, char *file_name);
void			free_map_info(t_map_info **map_info);
int				get_map_info(t_map_info **map_info, char **line);
int				map_reader(t_canvas *canvas_ptr, int fd, char **line);

/*
**	reader_tool.c
*/
void			map_info_insert_last(t_map_info **lst, t_map_info **target);

/*
**	path_tool.c
*/
const char		*check_resolution_line(const char *line, int *val, int max_val);
int				get_resolution(t_canvas *canvas_ptr, const char *line);
int				get_wall_texture(t_canvas *canvas_ptr, const char *line, int d);
const char		*extend_object_reader(const char *line, int *label, int *pose);
int				get_object_texture(t_canvas *canvas_ptr, const char *line);

/*
**	path_function.c
*/
int				is_map_line(const char *line);
int				is_empty_line(const char *line);
int				simple_atoi(char *str);
int				get_rgb(t_canvas *canvas_ptr, char *str, int d);
char			*trim_space(const char *line);

/*
**	map_tool.c
*/
int				**init_map(int row_size, int col_size);
int				extract_map_info(t_canvas *canvas_ptr, int **map, \
				t_map_info *map_info, int row_idx);
int				make_map(t_canvas *canvas_ptr, int **map, t_map_info *map_info);
int				check_map(int **map, int size[2]);
int				**get_map(t_canvas *canvas_ptr, t_map_info *map_info);

/*
**	map_function.c
*/
void			free_map(int ***map, int col_size);
int				get_map_row_size(t_map_info *map_info);
int				get_map_col_size(t_map_info *map_info);
int				dfs(int **map, int **map_visit, int idx[2], int size[2]);

/*
**	obj.c
*/
t_obj			*search_obj_id(t_obj *target_ptr, int id);
t_obj			*search_obj(t_obj *target_ptr, int x_int, int y_int);
int				add_obj(t_canvas *canvas_ptr, double x_loc, double y_loc, \
				int label);
int				remove_obj(t_canvas *canvas_ptr, int id);
void			free_obj(t_canvas *canvas_ptr);

/*
**	obj_in_view.c
*/
int				put_obj_info(t_obj_info **obj_info, t_obj *obj, double x_loc, \
				double y_loc);
void			free_obj_info(t_obj_info **obj_info);
void			update_obj_info(t_obj_info *obj_info, t_wall_info *wall_info, \
				int w, double angle_vec[2]);
void			sort_obj_info_loop(t_obj_info **obj_info, int cnt);
void			sort_obj_info(t_obj_info **obj_info);

/*
**	obj_in_view_tool.c
*/
t_obj_info		*search_obj_info(t_obj_info *target_ptr, int id);

/*
**	img.c
*/
t_img			*search_img(t_img *target_ptr, int label, int sub_label);
int				add_xpm_img(t_canvas *canvas_ptr, char *file_name, int label, \
				int sub_label);
int				add_color(t_canvas *canvas_ptr, int label, int sub_label, \
				int color);
void			free_img(t_canvas *canvas_ptr);

/*
**	save_bmp.c
*/
void			put_uint_to_char(unsigned char *box, uint32_t num);
int				put_bmp_header(int fd, t_canvas *canvas_ptr, \
				uint32_t file_size);
int				put_bmp_pixel(int fd, t_canvas *canvas_ptr);
int				save_bmp(t_canvas *canvas_ptr);

/*
**	angle_and_move.c
*/
void			change_angle(t_canvas *canvas_ptr);
void			check_and_move(t_canvas *canvas_ptr, double cos_val, \
				double sin_val);
int				movement(t_canvas *canvas_ptr);

/*
**	hook_control.c
*/
int				key_press_hook(int keycode, t_canvas *canvas_ptr);
int				key_release_hook(int keycode, t_canvas *canvas_ptr);
int				mouse_press_hook(int button, int x, int y, \
				t_canvas *canvas_ptr);
int				mouse_release_hook(int button, int x, int y, \
				t_canvas *canvas_ptr);
int				mouse_move_hook(int x, int y, t_canvas *canvas_ptr);

/*
**	hook1.c
*/
int				close_hook(t_canvas *canvas_ptr);
void			move_hook(int keycode, t_canvas *canvas_ptr, int is_press);
void			angle_hook(int keycode, t_canvas *canvas_ptr, int is_press);
void			door_hook(t_canvas *canvas_ptr);
void			jump_hook(int keycode, t_canvas *canvas_ptr);

/*
**	hooks2.c
*/
void			gun_hook(t_canvas *canvas_ptr);

/*
**	status.c
*/
void			eye(t_canvas *canvas_ptr, int info[3]);
void			potion_react(t_canvas *canvas_ptr);
void			dmg_react(t_canvas *canvas_ptr);
int				check_my_loc(t_canvas *canvas_ptr);
int				check_status(t_canvas *canvas_ptr);

/*
**	dda.c
*/
void			dda_init(t_canvas *canvas_ptr, double ray_vec[2], \
				int loc_int[4], double distance[4]);
int				dda_loop(t_canvas *canvas_ptr, t_obj_info **obj_info, \
				int loc_int[4], double distance[4]);
void			dda(t_canvas *canvas_ptr, t_wall_info *wall_info, \
				t_obj_info **obj_info, double ray_vec[2]);

/*
**	view_render.c
*/
void			bg_wall_render(t_canvas *canvas_ptr, t_wall_info *wall_info, \
				double ray_vec[2], int w);
void			objs_render(t_canvas *canvas_ptr, t_obj_info **obj_info, \
				double angle_vec[2]);
int				view_render(t_canvas *canvas_ptr);
void			option_render(t_canvas *canvas_ptr);
void			update_view(t_canvas *canvas_ptr);

/*
**	render_tool.c
*/
void			insert_filter(t_canvas *canvas_ptr, int r, int g, int b);
int				get_bg_color(t_canvas *canvas_ptr, t_img *target_ptr, \
				double ray_vec[2], int pixel);
void			get_obj_render_info(t_canvas *canvas_ptr, \
				t_obj_info *obj_info, double angle_vec[2], int render_info[5]);
void			objs_render_loop(t_canvas *canvas_ptr, t_obj_info *obj_info, \
				t_img *obj_img, int render_info[5]);
int				get_shade(int color, double shade_val);

/*
**	hud_render.c
*/
void			hud_render(t_canvas *canvas_ptr);
void			update_hud(t_canvas *canvas_ptr);
void			health_writer(t_canvas canvas, int x_loc, int y_loc, int color);
void			ending_writer(t_canvas canvas, char *word, int color, \
				int size_ratio);
void			bullet_writer(t_canvas canvas);

/*
**	animation.c
*/
void			jump_animation(t_canvas *canvas_ptr);
void			gun_animation(t_canvas *canvas_ptr);
void			animation(t_canvas *canvas_ptr);
void			enemy_die_animation(t_canvas *canvas_ptr, t_obj *enemy, \
				unsigned long current_time);
void			enemy_fire_animation(t_canvas *canvas_ptr, t_obj *enemy, \
				double enemy_ray[2], unsigned long current_time);

/*
**	option.c
*/
void			draw_aim(t_canvas *canvas_ptr);
void			draw_gun(t_canvas *canvas_ptr);
void			draw_full(t_canvas *canvas_ptr, t_img *img_ptr);

/*
**	enemy.c
*/
int				enemy_ray_to_me(t_canvas *canvas_ptr, double enemy_ray[2], \
				int enemy_x, int enemy_y);
int				enemy_check_and_move(t_canvas *canvas_ptr, t_obj *enemy, \
				double dx, double dy);
void			enemy_movement(t_canvas *canvas_ptr, t_obj *enemy, \
				double enemy_ray[2], unsigned long current_time);
void			enemy_control(t_canvas *canvas_ptr, t_obj *enemy, \
				double enemy_ray[2]);
void			enemies(t_canvas *canvas_ptr);

/*
**	enemy_tool.c
*/
void			enemy_gun_react(t_canvas *canvas_ptr, t_obj *enemy);
int				get_enemy_mv_idx(int theta);

/*
**	sound.c
*/
t_sound			*search_sound(t_sound *target_ptr, int id);
int				add_sound(t_canvas *canvas_ptr, char *filename, int id);

/*
**	function.c
*/
unsigned long	get_ms(struct timespec current);
int				wait_ending(unsigned long ms);
int				print_error(const char *s);

/*
**	get_next_line.c
*/
int				fd_read(int fd, char **storage_ptr);
int				get_line(char **storage_ptr, char **line);
int				get_next_line(int fd, char **line);

/*
**	get_next_line_utils.c
*/
int				search_idx(const char *str, char target);
char			*ft_strjoin(const char *src1, const char *src2);

#endif
