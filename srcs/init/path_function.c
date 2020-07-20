#include "cub3d.h"

int			is_map_line(const char *line)
{
	int			idx;

	idx = 0;
	while (line[idx] == ' ')
		idx++;
	if (line[idx] >= '0' && line[idx] <= '9')
		return (1);
	return (0);
}

int			is_empty_line(const char *line)
{
	char		exception;
	int			idx;

	exception = '#';
	idx = 0;
	while (line[idx] == ' ')
		idx++;
	if (line[idx] != 0 && line[idx] != exception)
		return (print_error("Wrong line") - 1);
	return (1);
}

char			*trim_space(const char *line)
{
	char		*out;
	int			idx;
	int			out_idx;
	int			start;
	int			end;

	idx = 0;
	while (line[idx] == ' ')
		idx++;
	start = idx;
	while (line[idx] != ' ' && line[idx] != 0)
		idx++;
	end = idx;
	if (!(out = (char *)malloc(sizeof(char) * (end - start + 1))))
		return (0);
	out_idx = 0;
	while (out_idx < end - start)
	{
		out[out_idx] = line[start + out_idx];
		out_idx++;
	}
	out[out_idx] = 0;
	return (out);
}

