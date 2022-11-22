# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 17:26:00 by jcourtoi          #+#    #+#              #
#    Updated: 2022/11/15 12:39:04 by jcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D 

SRCS =	srcs_n/main.c raycasting_n/raycasting.c raycasting_n/raycast_utils.c \
		raycasting_n/raycast_utils2.c srcs_n/init.c srcs_n/hooks.c \
		srcs_n/first_check.c parsing_n/parse.c parsing_n/init.c \
		parsing_n/init_utils.c parsing_n/parse_utils.c parsing_n/simple_parse.c\
		parsing_n/init_utils2.c srcs_n/free.c parsing_n/find_walls.c \
		parsing_n/init_path_utils.c parsing_n/get_colors.c \
		gnl_n/get_next_line.c gnl_n/get_next_line_utils.c\
		srcs_n/free_bis.c parsing_n/get_colors_utils.c srcs_n/moves.c\

		#srcs_n/parsing/parse.c srcs_n/free.c\
		gnl_n/get_next_line.c gnl_n/get_next_line_utils.c\
		srcs_n/init/init.c srcs_n/init/init_utils.c srcs_n/drawing.c\
		srcs_n/parsing/simple_parse.c srcs_n/parsing/parse_utils.c\
		srcs_n/parsing/find_walls.c srcs_n/hooks.c srcs_n/render.c\
		srcs_n/moves/move.c srcs_n/init/init_path_utils.c\
		srcs_n/free_bis.c srcs_n/init/get_colors.c srcs_n/draw_2d.c \
		srcs_n/bitshift.c srcs_n/init/init_utils2.c srcs_n/utils.c\
		srcs_n/init/init_player.c
		#srcs_n/init/init_ray.c srcs_n/raycasting/raycast_utils.c\
		srcs_n/raycasting/raycasting.c srcs_n/raycasting/raycast_utils2.c\
		#srcs_n/raycasting/drawing_rays.c

_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m
_END=	$'\033[0m

OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

INCLUDE =	-I inc_n\
		-I libft_n \
		-I minilibx\
		-I gnl_n\

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -Iminilibx -g3 #-fsanitize=address
CPPFLAGS = -MMD
MLXFLAGS = -Lmlx_linux -Imlx_linux -lXext -lX11 -lm -lz

RM = rm -rf

all: ${NAME}

%.o: %.c Makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) -I inc_n -I gnl_n $< -c -o $@

${NAME}: ${OBJS}
	@make -C ./libft_n
	@echo "$(_GREEN)Libft compiled$(_END)"
	@make -C ./minilibx
	@echo "$(_GREEN)minilibx compiled$(_END)"
	@echo "$(_GREEN)Executable created : cub3D$(_END)"
	${CC}  -o $(NAME) $(OBJS) ./libft_n/libft.a ./minilibx/libmlx_Linux.a $(MLXFLAGS)
#${CC} ${MLXFLAGS} ${CFLAGS} ${OBJS} ./libft_n/libft.a -o ${NAME}

clean:
	${RM} ${OBJS} ${DEPS}
	@make -C ./libft_n fclean
	@make -C ./minilibx/ clean
	@echo "$(_RED).o/.d files removed$'\033[0m"

fclean: clean
	${RM} ${NAME}
	@echo "$(_RED)Executable removed$'\033[0m"

re: fclean
	@make all

vtest: ${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME} maps/test.cub 

test: ${NAME}
	./${NAME} maps/test.cub

-include ${DEPS}
.PHONY: all clean fclean re bonus
