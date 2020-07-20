#ifndef INIT_H
# define INIT_H

#include <CoreGraphics/CGDisplayConfiguration.h>

typedef struct	s_map_info
{
	int			order;
	int			len;
	const char	*row_info;

	struct s_map_info	*next;

}				t_map_info;

#endif
