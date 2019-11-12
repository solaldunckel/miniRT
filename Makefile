# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2019/11/12 00:28:22 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= miniRT

SRCS_LIST		= \
					main.c \
					parse.c \
					parse_objs.c \
					events.c \
					raytrace.c \
					colors.c \
					bmp.c \
					vec.c \
					vec_2.c \
					sphere.c \
					plane.c \
					cylinder.c \
					square.c \
					triangle.c \
					ft.c

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

OBJS			= ${SRCS:.c=.o}

HEADER			= includes
FOLDER			= srcs

LIBFT 			= libft

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
LFLAGS			= -lmlx -framework OpenGL -framework AppKit
RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(HEADER) $(LIBFT)/libft.a $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) img.bmp
				@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re
