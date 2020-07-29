/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 21:18:37 by sseo              #+#    #+#             */
/*   Updated: 2020/07/22 21:57:16 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			fd_read(int fd, char **storage_ptr)
{
	int				len;
	int				lf_idx;
	char			*temp;
	char			*buf;

	len = 0;
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-2);
	while ((lf_idx = search_idx((const char *)*storage_ptr, '\n') == -1) && \
			(len = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[len] = 0;
		if (!(temp = ft_strjoin((const char *)*storage_ptr, (const char *)buf)))
			break ;
		free(*storage_ptr);
		*storage_ptr = temp;
	}
	free(buf);
	buf = 0;
	if (len < 0)
		return (-1);
	if (lf_idx == -1 && len > 0)
		return (-2);
	return (0);
}

int			get_line(char **storage_ptr, char **line)
{
	char			*temp;
	int				idx;
	int				len;
	int				is_eof;
	int				split_idx;

	idx = -1;
	len = search_idx((const char *)*storage_ptr, 0);
	split_idx = search_idx((const char *)*storage_ptr, '\n');
	is_eof = (split_idx == -1) ? 1 : 0;
	if (is_eof)
		split_idx = len;
	if (!(*line = (char *)malloc(sizeof(char) * (split_idx + 1))))
		return (-2);
	while (++idx < split_idx)
		(*line)[idx] = (*storage_ptr)[idx];
	(*line)[split_idx] = 0;
	if (!(temp = (char *)malloc(sizeof(char) * (len - split_idx + is_eof))))
		return (-2);
	while (++idx < len + is_eof)
		temp[idx - split_idx - 1] = (*storage_ptr)[idx];
	temp[idx - split_idx - 1] = 0;
	free(*storage_ptr);
	*storage_ptr = temp;
	return (1 - is_eof);
}

int			get_next_line(int fd, char **line)
{
	int				fd_read_error;
	int				get_line_status;
	static char		*storage;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == 0)
		return (-1);
	if (!storage)
	{
		storage = (char *)malloc(sizeof(char));
		*storage = 0;
	}
	fd_read_error = fd_read(fd, &storage);
	if (fd_read_error < 0)
		return (fd_read_error);
	get_line_status = get_line(&storage, line);
	return (get_line_status);
}
