/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:48:44 by sseo              #+#    #+#             */
/*   Updated: 2020/07/23 18:48:46 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		put_uint_to_char(unsigned char *box, uint32_t num)
{
	box[0] = (unsigned char)num;
	box[1] = (unsigned char)(num >> 8);
	box[2] = (unsigned char)(num >> 16);
	box[3] = (unsigned char)(num >> 24);
}

int			put_bmp_header(int fd, t_canvas *canvas_ptr, uint32_t file_size)
{
	int					idx;
	unsigned char		bmp_header[BMP_HEADER_SIZE];

	idx = 0;
	while (idx < BMP_HEADER_SIZE)
		bmp_header[idx++] = 0;
	bmp_header[0] = 'B';
	bmp_header[1] = 'M';
	put_uint_to_char(bmp_header + 2, file_size);
	bmp_header[10] = BMP_HEADER_SIZE;
	bmp_header[14] = BMP_INFO_HEADER_SIZE;
	put_uint_to_char(bmp_header + 18, canvas_ptr->width);
	put_uint_to_char(bmp_header + 22, \
			canvas_ptr->height);
	bmp_header[26] = 1;
	bmp_header[28] = 24;
	if (write(fd, bmp_header, BMP_HEADER_SIZE) < 0)
		return (1);
	return (0);
}

int			put_bmp_pixel(int fd, t_canvas *canvas_ptr)
{
	int					w_idx;
	int					h_idx;
	int					color;

	h_idx = canvas_ptr->height - 1;
	while (h_idx >= 0)
	{
		w_idx = 0;
		while (w_idx < canvas_ptr->width)
		{
			color = canvas_ptr->view_data[w_idx + \
					h_idx * canvas_ptr->sl / 4] & 0xFFFFFF;
			if (write(fd, &color, 3) < 0)
				return (1);
			w_idx++;
		}
		h_idx--;
	}
	return (0);
}

int			save_bmp(t_canvas *canvas_ptr)
{
	static const char	*file_name = "screenshot.bmp";
	uint32_t			file_size;
	int					fd;

	update_view(canvas_ptr);
	file_size = BMP_HEADER_SIZE + canvas_ptr->width * 3 * \
				(canvas_ptr->height);
	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND)) < 0)
		return (1);
	if (put_bmp_header(fd, canvas_ptr, file_size))
		return (1);
	if (put_bmp_pixel(fd, canvas_ptr))
		return (1);
	close(fd);
	close_hook(canvas_ptr);
	return (0);
}
