#include "cub3d.h"

t_obj			*search_obj_id(t_obj *target_ptr, int id)
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

t_obj			*search_obj(t_obj *target_ptr, int x_int, int y_int)
{
	while (target_ptr)
	{
		if (target_ptr->x_int == x_int && target_ptr->y_int == y_int)
			break ;
		target_ptr = target_ptr->next;
	}
	if (!target_ptr)
		return (0);
	return (target_ptr);
}

int				add_obj(t_canvas *canvas_ptr, double x_loc, double y_loc, int label)
{
	static int	id;
	t_obj		*new;
	t_obj		*target_ptr;

	target_ptr = canvas_ptr->objs;
	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		return (print_error(strerror(errno)));
	if (!target_ptr)
		id = 0;
	id++;
	new->id = id;
	new->x_int = (int)x_loc;
	new->y_int = (int)y_loc;
	new->x_loc = x_loc;
	new->y_loc = y_loc;
	new->label = label;
	new->pose = 0;
	new->angle = 0;
	new->last_clock = 0;
	new->next = target_ptr;
	canvas_ptr->objs = new;
	return (0);
}

int				remove_obj(t_canvas *canvas_ptr, int id)
{
	t_obj		*before;
	t_obj		*current;

	current = canvas_ptr->objs;
	if (!current)
		return (print_error("No object target"));
	if (current->id == id)
		canvas_ptr->objs = current->next;
	else
	{
		while (current)
		{
			before = current;
			current = current->next;
			if (!current)
				return (print_error("No matching object target"));
			if (current->id == id)
			{
				before->next = current->next;
				break ;
			}
		}
	}
	free(current);
	return (0);
}

void			free_obj(t_canvas *canvas_ptr)
{
	t_obj		*current;
	t_obj		*after;

	current = canvas_ptr->objs;
	while (current)
	{
		after = current->next;
		free(current);
		current = after;
	}
	canvas_ptr->objs = 0;
}
