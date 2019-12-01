/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:31:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/01 21:44:31 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct	s_res
{
	int			x;
	int			y;
	int			parsed;
}				t_res;

typedef struct	s_ray
{
	t_vec		ori;
	t_vec		dir;
}				t_ray;

typedef struct	s_solve
{
	float		a;
	float		b;
	float		c;
	float		det;
	float		t1;
	float		t2;
	float		d1;
	float		d2;
	t_vec		sub;
	t_vec		cross;
}				t_solve;

typedef struct	s_ambient
{
	float		ratio;
	int			parsed;
	t_color		color;
}				t_ambient;

typedef struct	s_image
{
	void		*ptr;
	char		*add;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_camera
{
	t_vec		pov;
	t_vec		orient;
	t_image		img;
	t_vec		up;
	t_vec		right;
}				t_camera;

typedef struct	s_texture
{
	void		*ptr;
	char		*img;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct	s_element
{
	int			id;
	t_vec		point;
	t_color		color;
	t_vec		orient;
	float		ratio;
	float		diameter;
	float		height;
	t_vec		point2;
	t_vec		point3;
	t_vec		dir;
	t_texture	tex;
	float		ref;
	int			nm;
	int			rainbow;
}				t_element;

#endif
