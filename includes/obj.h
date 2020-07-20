/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:35:49 by sseo              #+#    #+#             */
/*   Updated: 2020/07/18 16:58:44 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

/*
**	BLOCK LABEL
*/
# define WALL 1
# define DECO_1 2

#ifdef EXTEND_VERSION

# define ENEMY 3
# define BOSS 4
# define CLOSE_DOOR 5

/*
**	NON-BLOCK LABEL
*/
# define DECO_2 6
# define POTION 7
# define TRAP 8
# define BULLET 9

/*
**	DUMMY LABEL
*/
# define ENDING 10
# define DEAD_ENEMY 11
# define DEAD_BOSS 12
# define OPEN_DOOR 13

# define MAX_LABEL 13

#else

# define MAX_LABEL 2
#endif


typedef struct	s_obj
{
	int			id;
	int			label;
	int			pose;
	unsigned long	last_clock;

	int			x_int;
	int			y_int;
	double		x_loc;
	double		y_loc;
	int			angle;

	struct s_obj	*next;

}				t_obj;

#endif
