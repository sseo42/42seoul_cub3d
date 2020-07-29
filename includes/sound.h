/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:25:22 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 08:18:17 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# include "SDL.h"
# include "SDL_mixer.h"

# define RUN_SOUND 1
# define FIRE_SOUND 2
# define DIE_SOUND 3
# define HIT_SOUND 4
# define HIT2_SOUND 5
# define POTION_SOUND 6
# define RELOAD_SOUND 7
# define DOOR_SOUND 8
# define BGM_BASIC 0
# define BGM_RUSH 1
# define BGM_VICTORY 3
# define BGM_ENDING 4

typedef struct			s_sound
{
	int					id;
	Mix_Chunk			*s;
	struct s_sound		*next;
}						t_sound;

#endif
