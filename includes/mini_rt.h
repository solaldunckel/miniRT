/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/12 12:34:47 by sdunckel         ###   ########.fr       */
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

# define DEBUG_PARSING 0

# define CAMERA "CAMERA"
# define LIGHT "LIGHT"
# define SPHERE "SPHERE"
# define PLANE "PLANE"
# define SQUARE "SQUARE"
# define CYLINDER "CYLINDER"
# define TRIANGLE "TRIANGLE"

# define BMP_FILE_NAME "img.bmp"
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40
# define BMP_HEADER_SIZE BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE

# define R_TO_H(c) (((c.r & 0xff) << 16) + ((c.g & 0xff) << 8) + (c.b & 0xff))
# define DEG_TO_RAD(x) ((x * M_PI) / 180)
# define VEC_ADD(v) (v.x + v.y + v.z)
# define VEC_CREATE(x,y,z) ((t_vec){x,y,z})

typedef struct	s_mini_rt
{
	int					save;
	char				*line;
	char				**split;
	void				*mlx_ptr;
	void				*win_ptr;
	u_int				color;
	double				t;
	double				k;
	int					cur_cam;
	int					cam_count;
	struct s_image		img;
	struct s_res		res;
	struct s_ambient	ambient;
	struct s_ray		ray;
	struct s_element	*obj;
	struct s_element	*cam;
	struct s_list		*elem_list;
	struct s_list		*cam_list;
	struct s_list		*light_list;
}				t_mini_rt;

/*
** Parsing functions
*/
void			parse_rt_file(char *rt_file, t_mini_rt *rt);
int				parse_res(t_mini_rt *rt);
int				parse_ambient(t_mini_rt *rt);
int				parse_camera(t_mini_rt *rt);
int				parse_light(t_mini_rt *rt);
int				parse_sphere(t_mini_rt *rt);
int				parse_plane(t_mini_rt *rt);
int				parse_square(t_mini_rt *rt);
int				parse_cylindre(t_mini_rt *rt);
int				parse_triangle(t_mini_rt *rt);
int				check_split(t_mini_rt *rt);
void			free_split(char **split);
t_vec			split_vec(char *str, t_mini_rt *rt);
t_color			split_rgb(char *str, t_mini_rt *rt);

/*
** Events
*/
int				get_keypress(int key, t_mini_rt *rt);
int				handle_error(char *str, t_mini_rt *rt);
int				exit_and_free(t_mini_rt *rt);
void			free_element(void *elem);

/*
** Raytracing functions
*/
int				raytracing(t_mini_rt *rt);

/*
** Objects
*/
void			select_cam(t_mini_rt *rt);
int				intersect(double a, double b, double det);
void			sphere(t_mini_rt *rt, t_element *sphere);
void			cylinder(t_mini_rt *rt, t_element *cylinder);
void			plane(t_mini_rt *rt, t_element *plane);

/*
** Colors
*/
int				color_put(t_mini_rt *rt, int x, int y);
int				convert_rgb(t_color color);

/*
** Vectors
*/
t_vec			vec_add(t_vec v1, t_vec v2);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_mul(t_vec v1, double m);
t_vec			vec_div(t_vec v1, double d);
t_vec			vec_dot(t_vec v1, t_vec v2);
void			rotate_vector(t_vec *v, t_vec *rot);
void			vec_normalize(t_vec *v);

/*
** Additional functions
*/
void			create_bmp_image(t_mini_rt *rt, char *file_name);

#endif
