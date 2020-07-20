/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:25:22 by sseo              #+#    #+#             */
/*   Updated: 2020/07/16 13:40:29 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# define RUN_SOUND 1
# define FIRE_SOUND 2
# define DIE_SOUND 3
# define HIT_SOUND 4
# define POTION_SOUND 5
# define RELOAD_SOUND 6

# define BGM_BASIC 0
# define BGM_ENDING 4

# include "SDL.h"
# include "SDL_mixer.h"

typedef struct	s_sound
{
	int			id;
	Mix_Chunk	*s;

	struct s_sound		*next;

}				t_sound;

#endif
