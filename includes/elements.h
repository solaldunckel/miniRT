/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:31:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 18:11:17 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

typedef struct	s_coords
{
	double		x;
	double		y;
	double		z;
}				t_coords;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_res
{
	int			x;
	int			y;
}				t_res;

typedef struct	s_ambient
{
	double			ratio;
	struct s_color	color;
}				t_ambient;

typedef struct	s_camera
{
	struct s_coords	pov;
	struct s_coords	orient;
	struct s_camera	*next;
}				t_camera;

typedef struct	s_light
{
	struct s_coords	point;
	double			ratio;
	struct s_color	color;
	struct s_light	*next;
}				t_light;

typedef struct	s_sphere
{
	struct s_coords	point;
	double			diameter;
	struct s_color	color;
	struct s_sphere	*next;
}				t_sphere;

typedef struct	s_plane
{
	struct s_coords	point;
	struct s_coords	orient;
	struct s_color	color;
	struct s_plane	*next;
}				t_plane;

typedef struct	s_square
{
	struct s_coords	point;
	struct s_coords	orient;
	double			height;
	struct s_color	color;
	struct s_square	*next;
}				t_square;

typedef struct	s_cylinder
{
	struct s_coords		point;
	struct s_coords		orient;
	double				diameter;
	double				height;
	struct s_color		color;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct	s_triangle
{
	struct s_coords		point1;
	struct s_coords		point2;
	struct s_coords		point3;
	struct s_color		color;
	struct s_triangle	*next;
}				t_triangle;

#endif
