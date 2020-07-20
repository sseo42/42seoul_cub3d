#include "cub3d.h"

t_sound			*search_sound(t_sound *target_ptr, int id)
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

int				add_sound(t_canvas *canvas_ptr, char *filename, int id)
{
	t_sound		*new;
	t_sound		*target_ptr;

	if (!(new = (t_sound *)malloc(sizeof(t_sound))))
		return (print_error(strerror(errno)));
	new->id = id;
	if (!(new->s = Mix_LoadWAV(filename)))
		return (print_error(SDL_GetError()));
	new->next = 0;
	target_ptr = canvas_ptr->sounds;
	if (!target_ptr)
		canvas_ptr->sounds = new;
	else
	{
		while (target_ptr->next)
			target_ptr = target_ptr->next;
		target_ptr->next = new;
	}
	return (0);
}

