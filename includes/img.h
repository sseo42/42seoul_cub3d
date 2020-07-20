/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:45:22 by sseo              #+#    #+#             */
/*   Updated: 2020/07/17 19:38:48 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

/*
**	IMAGE DIRECTION (SUB LABEL)
*/
# define EAST 0
# define WEST 1
# define NORTH 2
# define SOUTH 3
# define UP 4
# define DOWN 5

/*
**	IMAGE CONSTANTS FOR ANIMATION
*/
# define DEFAULT_POSE 0
# define GUN_MOTION_NUM 5
# define ENEMY_DIE_MOTION_POSE 36
# define ENEMY_DIE_MOTION_NUM 5
# define ENEMY_FIRE_MOTION_POSE 32
# define ENEMY_FIRE_MOTION_NUM 3
# define ENEMY_MOVE_MOTION_NUM 32
# define ENEMY_POSE_CLOCK 300000
# define ENEMY_DIE_POSE_CLOCK 30000

typedef struct	s_img
{
	void		*img;
	int			*data;

	int			bg_color;
	int			label;
	int			sub_label;
	int			width;
	int			height;
	int			bpp;		//bits per pixel
	int			sl;			//size line
	int			endian;

	struct s_img		*next;

}				t_img;

#endif
