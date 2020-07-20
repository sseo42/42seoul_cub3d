#include "cub3d.h"

void		insert_filter(t_canvas *canvas_ptr, int r, int g, int b)
{
	int			i;
	int			len;
	int			red;
	int			green;
	int			blue;

	i = 0;
	len = canvas_ptr->width * canvas_ptr->height;
	while (i < len)
	{
		red = (canvas_ptr->view_buf[i] >> 16) % 256 + r;
		green = (canvas_ptr->view_buf[i] >> 8) % 256 + g;
		blue = (canvas_ptr->view_buf[i]) % 256 + b;
		if (red >= 256)
			red = 255;
		if (green >= 256)
			green = 255;
		if (blue >= 256)
			blue = 255;
		canvas_ptr->view_buf[i] = (red << 16) + (green << 8) + blue;
		i++;
	}
}

int			get_bg_color(t_canvas *canvas_ptr, t_img *target_ptr, double ray_vec[2], int pixel)
{
	double		row_distance;
	double		bg_x;
	double		bg_y;
	int			color;

	row_distance = 0.5 * canvas_ptr->height / abs(pixel - canvas_ptr->horizon_line);
	bg_x = canvas_ptr->x_loc + ray_vec[0] * row_distance;
	bg_y = canvas_ptr->y_loc - ray_vec[1] * row_distance;
	bg_x = (bg_x - floor(bg_x)) * target_ptr->width;
	bg_y = (bg_y - floor(bg_y)) * target_ptr->height;
	color = get_shade(target_ptr->data[(int)bg_y * target_ptr->sl / 4 + \
			(int)bg_x], row_distance, SHADE_INTENSITY);
	return (color);
}

void		get_obj_render_info(t_canvas *canvas_ptr, t_obj_info *obj_info, double angle_vec[2], int render_info[5])
{
	double				distance_from_angle;
	int					obj_x;
	int					obj_size;

	distance_from_angle = (obj_info->distance_x * angle_vec[1] - \
			obj_info->distance_y * angle_vec[0]) / canvas_ptr->plane_vec_scale;
	obj_x = (int)((canvas_ptr->width / 2) * (1 + distance_from_angle / obj_info->d_from_plane));
	obj_size = (int)(canvas_ptr->height / obj_info->d_from_plane);

	render_info[0] = obj_x - obj_size / 2;
	render_info[1] = obj_x + obj_size / 2;
	render_info[2] = canvas_ptr->horizon_line - obj_size / 2;
	render_info[3] = canvas_ptr->horizon_line + obj_size / 2;
	if (render_info[1] > canvas_ptr->width)
		render_info[1] = canvas_ptr->width;
	if (render_info[3] > canvas_ptr->height)
		render_info[3] = canvas_ptr->height;
	render_info[4] = obj_size;
}

void		objs_render_loop(t_canvas *canvas_ptr, t_obj_info *obj_info, t_img *obj_img, int render_info[5])
{
	int					w_idx;
	int					h_idx;
	int					color;
	int					temp;

	w_idx = render_info[0] < 0 ? 0 : render_info[0];
	while (w_idx < render_info[1])
	{
		temp = (w_idx - render_info[0]) * obj_img->width;
		h_idx = render_info[2] < 0 ? 0 : render_info[2];
		while (h_idx < render_inf[3])
		{
			color = obj_img->data[(temp + (h_idx - render_info[2]) * \
					obj_img->height * obj_img->sl / 4) / render_info[4]];
			if (color != obj_img->bg_color && w_idx >= obj_info->w_start && \
					w_idx < obj_info->w_end)
			{
				color = get_shade(color, obj_info->d_from_plane, SHADE_INTENSITY);
				canvas_ptr->view_buf[h_idx * canvas_ptr->width + w_idx] = color;
				if (w_idx == canvas_ptr->width / 2 && h_idx == canvas_ptr->height / 2)
					canvas_ptr->at_my_aim = obj_info->id;
			}
			h_idx++;
		}
		w_idx++;
	}
}

int			get_shade(int color, double distance, double intensity)
{
	int			red;
	int			green;
	int			blue;

	red = (int)((canvas_ptr->view_buf[i] >> 16) % 256 / (distance * intensity));
	green = (int)((canvas_ptr->view_buf[i] >> 8) % 256 / (distance * intensity));
	blue = (int)((canvas_ptr->view_buf[i]) % 256 / (distance * intensity));
	return ((red << 16) + (green << 8) + blue);
}
