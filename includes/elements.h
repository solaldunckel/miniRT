/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:31:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 09:28:58 by sdunckel         ###   ########.fr       */
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

typedef struct	s_image
{
	void				*ptr;
	char				*add;
	int					bbp;
	int					size_line;
	int					endian;
}				t_image;

typedef struct	s_element
{
	char				*id;
	struct s_coords		pov;
	struct s_coords		point;
	struct s_color		color;
	struct s_coords		orient;
	double				ratio;
	double				diameter;
	double				height;
	struct s_coords		point2;
	struct s_coords		point3;
}				t_element;

#endif
