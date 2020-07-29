/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:14:52 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 10:14:57 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		map_info_insert_last(t_map_info **lst, t_map_info **target)
{
	t_map_info		*lst_last;

	lst_last = *lst;
	if (*lst == 0)
		*lst = *target;
	else
	{
		while (lst_last->next)
			lst_last = lst_last->next;
		lst_last->next = *target;
	}
}
