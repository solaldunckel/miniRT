/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/29 18:27:35 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
# include "../libft/includes/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <stdio.h>

typedef struct 	s_mini_rt
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			res_x;
	int 		res_y;
	float		ambient_ratio;
	int			ambient_r;
	int			ambient_g;
	int			ambient_b;
}				t_mini_rt;

typedef struct 	s_camera
{
	float	pov_x;
	float 	pov_y;
	float 	pov_z;
	float	orient_x;
	float 	orient_y;
	float 	orient_z;
}				t_camera;

typedef struct 	s_light
{
	float	point_x;
	float 	point_y;
	float 	point_z;
	float	ratio;
	int		r;
	int 	g;
	int 	b;
}				t_light;

typedef struct 	s_sphere
{
	float	point_x;
	float 	point_y;
	float 	point_z;
	float	diameter;
	int		r;
	int 	g;
	int 	b;
}				t_sphere;

typedef struct 	s_plane
{
	float	point_x;
	float 	point_y;
	float 	point_z;
	float	orient_x;
	float 	orient_y;
	float 	orient_z;
	int		r;
	int 	g;
	int 	b;
}				t_plane;

typedef struct 	s_square
{
	float	point_x;
	float 	point_y;
	float 	point_z;
	float	orient_x;
	float 	orient_y;
	float 	orient_z;
	float	height;
	int		r;
	int 	g;
	int 	b;
}				t_square;

typedef struct 	s_cylinder
{
	float	point_x;
	float 	point_y;
	float 	point_z;
	float	orient_x;
	float 	orient_y;
	float 	orient_z;
	float	diameter;
	float	height;
	int		r;
	int 	g;
	int 	b;
}				t_cylinder;

typedef struct 	s_triangle
{
	float	point1_x;
	float 	point1_y;
	float 	point1_z;
	float	point2_x;
	float 	point2_y;
	float 	point2_z;
	float	point3_x;
	float 	point3_y;
	float 	point3_z;
	int		r;
	int 	g;
	int 	b;
}				t_triangle;


#endif
