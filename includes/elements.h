/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:31:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/01 14:13:00 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

typedef struct	s_res
{
	int			x;
	int			y;
}				t_res;

typedef struct	s_ambient
{
	double		ratio;
	int			r;
	int			g;
	int			b;
}				t_ambient;

typedef struct	s_camera
{
	double			pov_x;
	double			pov_y;
	double			pov_z;
	double			orient_x;
	double			orient_y;
	double			orient_z;
	struct s_camera	*next;
}				t_camera;

typedef struct	s_light
{
	double			point_x;
	double			point_y;
	double			point_z;
	double			ratio;
	int				r;
	int				g;
	int				b;
	struct s_light	*next;
}				t_light;

typedef struct	s_sphere
{
	double			point_x;
	double			point_y;
	double			point_z;
	double			diameter;
	int				r;
	int				g;
	int				b;
	struct s_sphere	*next;
}				t_sphere;

typedef struct	s_plane
{
	double			point_x;
	double			point_y;
	double			point_z;
	double			orient_x;
	double			orient_y;
	double			orient_z;
	int				r;
	int				g;
	int				b;
	struct s_plane	*next;
}				t_plane;

typedef struct	s_square
{
	double			point_x;
	double			point_y;
	double			point_z;
	double			orient_x;
	double			orient_y;
	double			orient_z;
	double			height;
	int				r;
	int				g;
	int				b;
	struct s_square	*next;
}				t_square;

typedef struct	s_cylinder
{
	double				point_x;
	double				point_y;
	double				point_z;
	double				orient_x;
	double				orient_y;
	double				orient_z;
	double				diameter;
	double				height;
	int					r;
	int					g;
	int					b;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct	s_triangle
{
	double				point1_x;
	double				point1_y;
	double				point1_z;
	double				point2_x;
	double				point2_y;
	double				point2_z;
	double				point3_x;
	double				point3_y;
	double				point3_z;
	int					r;
	int					g;
	int					b;
	struct s_triangle	*next;
}				t_triangle;

#endif
