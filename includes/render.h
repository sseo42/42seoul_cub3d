/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:56:02 by sseo              #+#    #+#             */
/*   Updated: 2020/07/22 21:34:24 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "img.h"

# define VIEWING_ANGLE 66
# define AIM_SIZE 30
# define AIM_COLOR 0255000000
# define HUD_COLOR 0000000255
# define STRING_COLOR1 0255000000
# define SHADE_INTENSITY 0.66

typedef struct				s_wall_info
{
	t_img					*wall_ptr;

	double					distance;
	int						line_height;
	int						draw_start;
	int						draw_end;
	int						wall_x;
}							t_wall_info;

typedef struct				s_obj_info
{
	int						id;
	int						label;
	int						pose;

	double					distance_x;
	double					distance_y;
	double					d_from_plane;

	int						w_start;
	int						w_end;
	int						update;

	struct s_obj_info		*next;
}							t_obj_info;

#endif
