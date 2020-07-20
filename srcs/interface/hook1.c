#include "cub3d.h"

int			close_hook(t_canvas *canvas_ptr)
{
	mlx_destroy_window(canvas_ptr->mlx, canvas_ptr->window);
	exit(0);
}

void		move_hook(int keycode, t_canvas *canvas_ptr, int is_press)
{
	if (keycode == WEST_KEY && is_press)
		canvas_ptr->horizon_mv_info |= 1;
	else if (keycode == WEST_KEY)
		canvas_ptr->horizon_mv_info &= 2;
	else if (keycode == EAST_KEY && is_press)
		canvas_ptr->horizon_mv_info |= 2;
	else if (keycode == EAST_KEY)
		canvas_ptr->horizon_mv_info &= 1;
	else if (keycode == NORTH_KEY && is_press)
		canvas_ptr->vertical_mv_info |= 1;
	else if (keycode == NORTH_KEY)
		canvas_ptr->vertical_mv_info &= 2;
	else if (keycode == SOUTH_KEY && is_press)
		canvas_ptr->vertical_mv_info |= 2;
	else if (keycode == SOUTH_KEY)
		canvas_ptr->vertical_mv_info &= 1;
	else
		printf("move_hook_error\n");
}

void		angle_hook(int keycode, t_canvas *canvas_ptr, int is_press)
{
	if (keycode == UP_KEY && is_press)
		canvas_ptr->tilting_spd = TILTING_SPD;
	else if (keycode == UP_KEY)
		canvas_ptr->tilting_spd = 0;
	else if (keycode == DOWN_KEY && is_press)
		canvas_ptr->tilting_spd = -TILTING_SPD;
	else if (keycode == DOWN_KEY)
		canvas_ptr->tilting_spd = 0;
	else if (keycode == RIGHT_KEY && is_press)
		canvas_ptr->rot_spd = -ROT_SPD;
	else if (keycode == RIGHT_KEY)
		canvas_ptr->rot_spd = 0;
	else if (keycode == LEFT_KEY && is_press)
		canvas_ptr->rot_spd = ROT_SPD;
	else if (keycode == LEFT_KEY)
		canvas_ptr->rot_spd = 0;
	else
		printf("angle_hook_error\n");
}

void		door_hook(t_canvas *canvas_ptr)
{
	int		door_info[3];
	
	eye(canvas_ptr, door_info);
	if (door_info[2] == CLOSE_DOOR)
	{
		canvas_ptr->map[door_info[1]][door_info[0]] = OPEN_DOOR;
		canvas_ptr->view_update = 1;
	}
	else if (door_info[2] == OPEN_DOOR)
	{
		canvas_ptr->map[door_info[1]][door_info[0]] = CLOSE_DOOR;
		canvas_ptr->view_update = 1;
	}
}

void		jump_hook(int keycode, t_canvas *canvas_ptr)
{
	if (keycode == JUMP_KEY && !canvas_ptr->jump_state)
		canvas_ptr->jump_state = JUMP_HEIGHT;
}
