# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2019/12/09 14:10:41 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= miniRT

SRCS_LIST		= \
					main.c \
					parse.c \
					parse_objs.c \
					parse_utils.c \
					parse_more.c \
					events.c \
					raytrace.c \
					colors.c \
					bmp.c \
					vec.c \
					vec_2.c \
					sphere.c \
					plane.c \
					cylinder.c \
					cone.c \
					square.c \
					triangle.c \
					camera.c \
					lights.c \
					circle.c \
					shadows.c \
					hooks.c \
					hooks_2.c \
					move_objs.c \
					texture.c \
					ft.c \
					reflect.c \
					utils.c \
					skybox.c

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

OBJS			= ${SRCS:.c=.o}

HEADER			= includes
FOLDER			= srcs

LIBFT 			= libft
MLX 			= minilibx

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft

OPENGL_MLX		= -lmlx -framework OpenGL -framework AppKit
METAL_MLX		= libmlx.dylib -framework Metal -framework AppKit

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) $(OPENGL_MLX) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

bonus:			$(NAME)

metal:			$(OBJS)
				@make -s -C $(MLX)
				@mv $(MLX)/libmlx.dylib .
				@make -s -j8 -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) $(METAL_MLX) -I $(HEADER) $(OBJS) -o $(NAME)

clean:
				@$(RM) $(OBJS)
				@make clean -C $(MLX)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) libmlx.dylib
				@$(RM) img.bmp
				@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re
