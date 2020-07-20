#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 100

int			get_next_line(int fd, char **line);
int			search_idx(const char *str, char target);
char		*ft_strjoin(const char *src1, const char *src2);

#endif
