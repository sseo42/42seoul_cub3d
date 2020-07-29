# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sseo <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/09 16:10:15 by sseo              #+#    #+#              #
#    Updated: 2020/07/23 19:17:49 by sseo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c						\
	   srcs/init/init.c					\
	   srcs/init/init_tool.c			\
	   srcs/init/reader.c				\
	   srcs/init/reader_tool.c			\
	   srcs/init/path_tool.c			\
	   srcs/init/path_function.c		\
	   srcs/init/map_tool.c				\
	   srcs/init/map_function.c			\
	   srcs/interface/angle_and_move.c	\
	   srcs/interface/hook_control.c	\
	   srcs/interface/hook1.c			\
	   srcs/interface/hook2.c			\
	   srcs/image/img.c					\
	   srcs/image/save_bmp.c			\
	   srcs/object/obj.c				\
	   srcs/object/enemy.c				\
	   srcs/object/enemy_tool.c			\
	   srcs/render/dda.c				\
	   srcs/render/view_render.c		\
	   srcs/render/obj_in_view.c		\
	   srcs/render/obj_in_view_tool.c	\
	   srcs/render/render_tool.c		\
	   srcs/render/hud_render.c			\
	   srcs/status/status.c				\
	   srcs/status/option.c				\
	   srcs/status/animation.c			\
	   srcs/sound/sound.c				\
	   srcs/functions/function.c		\
	   srcs/gnl/get_next_line.c			\
	   srcs/gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I minilibx/ -I includes/ \
		   -I SDL/SDL2.framework/Headers/ -I SDL/SDL2_mixer.framework/Headers/

LIBS = -lmlx -L. -framework OpenGl -framework AppKit -rpath @loader_path/SDL \
	   -framework SDL2 -F SDL/ -framework SDL2_mixer -F SDL/

all: $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C minilibx
	@cd minilibx; mv libmlx.dylib ../
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJS) -o cub3D
	@echo "DONE"

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

bonus: $(all)

clean:
	@cd minilibx; make clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all

bonus: all
