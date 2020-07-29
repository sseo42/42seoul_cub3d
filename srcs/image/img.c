/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:00:13 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 13:24:29 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img			*search_img(t_img *target_ptr, int label, int sub_label)
{
	while (target_ptr)
	{
		if (target_ptr->label == label && target_ptr->sub_label == sub_label)
			break ;
		target_ptr = target_ptr->next;
	}
	if (!target_ptr)
		return (0);
	return (target_ptr);
}

int				add_xpm_img(t_canvas *canvas_ptr, char *file_name, int label, \
		int sub_label)
{
	t_img		*img_ptr;
	t_img		*new;

	img_ptr = canvas_ptr->imgs;
	printf("add image file: %s\n", file_name);
	if (!(new = (t_img *)malloc(sizeof(t_img))))
		return (print_error(strerror(errno)));
	new->label = label;
	new->sub_label = sub_label;
	if (!(new->img = mlx_xpm_file_to_image(canvas_ptr->mlx, file_name, \
					&(new->width), &(new->height))))
		return (print_error(strerror(errno)));
	new->data = (int *)mlx_get_data_addr(new->img, \
			&(new->bpp), &(new->sl), &(new->endian));
	new->bg_color = new->data[0];
	new->next = 0;
	if (img_ptr)
	{
		while (img_ptr->next)
			img_ptr = img_ptr->next;
		img_ptr->next = new;
	}
	else
		canvas_ptr->imgs = new;
	return (0);
}

int				add_color(t_canvas *canvas_ptr, int label, int sub_label, \
				int color)
{
	t_img		*img_ptr;
	t_img		*new;

	img_ptr = canvas_ptr->imgs;
	if (!(new = (t_img *)malloc(sizeof(t_img))))
		return (print_error(strerror(errno)));
	new->label = label;
	new->sub_label = sub_label;
	new->data = 0;
	new->bg_color = color;
	new->width = 1;
	new->height = 1;
	new->sl = 4;
	new->next = 0;
	if (img_ptr)
	{
		while (img_ptr->next)
			img_ptr = img_ptr->next;
		img_ptr->next = new;
	}
	else
		canvas_ptr->imgs = new;
	return (0);
}

void			free_img(t_canvas *canvas_ptr)
{
	t_img		*current;
	t_img		*after;

	current = canvas_ptr->imgs;
	while (current)
	{
		after = current->next;
		free(current);
		current = after;
	}
	canvas_ptr->imgs = 0;
}
