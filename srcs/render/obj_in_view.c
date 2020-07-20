#include "cub3d.h"

t_obj_info		*search_obj_info(t_obj_info *target_ptr, int id)
{
	while (target_ptr)
	{
		if (target_ptr->id == id)
			break ;
		target_ptr = target_ptr->next;
	}
	if (!target_ptr)
		return (0);
	return (target_ptr);
}

int				put_obj_info(t_obj_info **obj_info, t_obj *obj, double x_loc, double y_loc)
{
	t_obj_info		*ptr;
	t_obj_info		*new;

	ptr = *obj_info;
	if (!(new = (t_obj_info *)malloc(sizeof(t_obj_info))))
		return (print_error(strerror(errno)));
	new->id = obj->id;
	new->label = obj->label;
	new->pose = obj->pose;
	new->distance_x = obj->x_loc - x_loc;
	new->distance_y = y_loc - obj->y_loc;
	new->d_from_plane = -1;
	new->update = 2;
	new->next = 0;
	if (!ptr)
		*obj_info = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (0);
}

void			free_obj_info(t_obj_info **obj_info)
{
	t_obj_info		*current;
	t_obj_info		*after;

	current = *obj_info;
	while (current)
	{
		after = current->next;
		free(current);
		current = after;
	}
	*obj_info = 0;
}

void			update_obj_info(t_obj_info *obj_info, t_wall_info *wall_info, int w, double angle_vec[2])
{
	static double		last_w_distance;

	while (obj_info)
	{
		if (obj_info->update)
		{
			if (obj_info->d_from_plane == -1)
			{
				obj_info->d_from_plane = fabs(obj_info->distance_x * angle_vec[0] + \
						obj_info->distance_y * angle_vec[1]);
				obj_info->w_start = 0;
				obj_info->w_end = INT_MAX;
				if (last_w_distance < obj_info->d_from_plane)
					obj_info->w_start = w;
			}
			if (wall_info->distance < obj_info->d_from_plane && obj_info->update == 1)
				obj_info->w_end = w;
			obj_info->update--;
		}
		obj_info = obj_info->next;
	}
	last_w_distance = wall_info->distance;
}

void			sort_obj_info_loop(t_obj_info **obj_info, int cnt)
{
	int				sub_cnt;
	t_obj_info		*before;
	t_obj_info		*ptr;
	t_obj_info		*after;

	sub_cnt = cnt;
	before = *obj_info;
	ptr = before->next;
	while (--sub_cnt > 0)
	{
		after = ptr->next;
		if (ptr->d_from_plane < after->d_from_plane)
		{
			before->next = after;
			ptr->next = after->next;
			after->next = ptr;
		}
		before = before->next;
		ptr = before->next;
	}
}

//bubble sorting
void			sort_obj_info(t_obj_info **obj_info)
{
	int				cnt;
	t_obj_info		*ptr;
	t_obj_info		*after;

	cnt = 0;
	ptr = *obj_info;
	while (ptr)
	{
		cnt++;
		ptr = ptr->next;
	}
	while (--cnt > 0)
	{
		ptr = *obj_info;
		after = ptr->next;
		if (ptr->d_from_plane < after->d_from_plane)
		{
			*obj_info = after;
			ptr->next = after->next;
			after->next = ptr;
		}
		sort_obj_info_loop(obj_info, cnt);
	}
}
