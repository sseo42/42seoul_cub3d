/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:52:09 by sseo              #+#    #+#             */
/*   Updated: 2020/07/22 21:52:12 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <CoreGraphics/CGDisplayConfiguration.h>

typedef struct			s_map_info
{
	int					order;
	int					len;
	const char			*row_info;

	struct s_map_info	*next;

}						t_map_info;

#endif
