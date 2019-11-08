/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 12:47:43 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "elements.h"
# include "../libft/includes/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include <stdio.h>

# define DEBUG_PARSING 1

typedef struct	s_mini_rt
{
	int					i;
	char				*line;
	void				*mlx_ptr;
	void				*win_ptr;
	int					x;
	int					y;
	struct s_list		*list;
	struct s_res		res;
	struct s_ambient	ambient;
	struct s_image		img;
}				t_mini_rt;

/*
** Parsing functions
*/
int				parse_res(t_mini_rt *rt);
int				parse_ambient(t_mini_rt *rt);
int				parse_camera(t_mini_rt *rt);
int				parse_light(t_mini_rt *rt);
int				parse_sphere(t_mini_rt *rt);
int				parse_plane(t_mini_rt *rt);
int				parse_square(t_mini_rt *rt);
int				parse_cylindre(t_mini_rt *rt);
int				parse_triangle(t_mini_rt *rt);
int				ft_strstr_rt(char *str, char *to_find, t_mini_rt *rt);
int				ft_atoi_rt(char *str, t_mini_rt *rt);
double			ft_atof_rt(char *str, t_mini_rt *rt);

/*
** Events
*/
int				get_keypress(int key, t_mini_rt *rt);
int				get_cross_button(t_mini_rt *rt);

/*
** Additional functions
*/
int				handle_error(char *str, t_mini_rt *rt);
int				exit_and_free(t_mini_rt *rt);

#endif
