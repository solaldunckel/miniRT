/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:31:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 01:43:41 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

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

typedef struct	s_ray
{
	struct s_vec	ori;
	struct s_vec	dir;
}				t_ray;

typedef struct	s_solve
{
	double		a;
	double		b;
	double		c;
	double		det;
	double		t1;
	double		t2;
}				t_solve;

typedef struct	s_ambient
{
	double			ratio;
	struct s_color	color;
}				t_ambient;

typedef struct	s_image
{
	void			*ptr;
	char			*add;
	int				bpp;
	int				size_line;
	int				endian;
}				t_image;

typedef struct	s_camera
{
	struct s_vec	pov;
	struct s_vec	orient;
	double			fov;
	struct s_image	img;
	struct s_vec	up;
	struct s_vec	right;
}				t_camera;

typedef struct	s_element
{
	int				id;
	struct s_vec	point;
	struct s_color	color;
	struct s_vec	orient;
	double			ratio;
	double			diameter;
	double			height;
	struct s_vec	point2;
	struct s_vec	point3;
	struct s_vec	dir;
}				t_element;

#endif
