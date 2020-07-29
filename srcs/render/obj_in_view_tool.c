/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_in_view_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:15:24 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 10:15:25 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
