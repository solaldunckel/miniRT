# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2019/11/01 16:03:00 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= miniRT

SRCS_LIST		= \
					mini_rt.c \
					ft_parse.c \
					ft_parse_2.c \
					ft_ft.c

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

OBJS			= ${SRCS:.c=.o}

HEADER			= includes
FOLDER			= srcs

LIBFT 			= libft
MINILIBX 		= minilibx

LIB				= $(MINILIBX)/libmlx.dylib $(LIBFT)/libft.a

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
LFLAGS			= -lmlx -framework OpenGL -framework AppKit
RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -C $(LIBFT)
				@make -C $(MINILIBX)
				@$(CC) $(CFLAGS) $(LFLAGS) -I $(HEADER) -L /usr/local/lib/ $(LIBFT)/libft.a $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)
				@make clean -C $(MINILIBX)

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re
