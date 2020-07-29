/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:36 by sseo              #+#    #+#             */
/*   Updated: 2020/07/22 21:56:08 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			search_idx(const char *str, char target)
{
	int				idx;

	idx = 0;
	while (str[idx] != target)
	{
		if (str[idx] == 0)
			return (-1);
		idx++;
	}
	return (idx);
}

char		*ft_strjoin(const char *src1, const char *src2)
{
	int				idx_1;
	int				idx_2;
	int				len_1;
	int				len_2;
	char			*out;

	idx_1 = 0;
	idx_2 = 0;
	len_1 = search_idx(src1, 0);
	len_2 = search_idx(src2, 0);
	if (!(out = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1))))
		return (0);
	while (idx_1 < len_1)
	{
		out[idx_1] = src1[idx_1];
		idx_1++;
	}
	while (idx_2 < len_2)
	{
		out[idx_1 + idx_2] = src2[idx_2];
		idx_2++;
	}
	out[len_1 + len_2] = 0;
	return (out);
}
