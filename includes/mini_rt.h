/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/01 16:05:18 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "elements.h"
# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
# include "../libft/includes/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include <stdio.h>

typedef struct	s_mini_rt
{
	int					i;
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_res		res;
	struct s_ambient	ambient;
}				t_mini_rt;

/*
** Parsing functions
*/

int		parse_res(t_mini_rt *rt, char *line);
int		parse_ambient(t_mini_rt *rt, char *line);
int		parse_camera(t_mini_rt *rt, char *line);
int		parse_light(t_mini_rt *rt, char *line);
int		parse_sphere(t_mini_rt *rt, char *line);
int		parse_plane(t_mini_rt *rt, char *line);
int		parse_square(t_mini_rt *rt, char *line);
int		parse_cylindre(t_mini_rt *rt, char *line);
int		parse_triangle(t_mini_rt *rt, char *line);

/*
** Additional functions
*/
int		ft_strstr_rt(char *str, char *to_find);
int		rgt_to_color(int r, int g, int b);
double	ft_atof(char *str);

#endif
