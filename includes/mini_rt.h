/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 14:44:43 by sdunckel         ###   ########.fr       */
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

# define SPHERE 1
# define PLANE 2
# define SQUARE 3
# define CYLINDER 4
# define TRIANGLE 5
# define CIRCLE 6

# define BMP_FILE_NAME "img.bmp"
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40
# define BMP_HEADER_SIZE BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE

# define R_TO_H(c) (((c.r & 0xff) << 16) + ((c.g & 0xff) << 8) + (c.b & 0xff))
# define VEC_ADD(v) (v.x + v.y + v.z)
# define VEC_CREATE(x,y,z) ((t_vec){x,y,z})

typedef struct	s_mini_rt
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					save;
	char				*line;
	char				**split;
	struct s_color		color;
	double				intensity;
	double				t;
	double				k;
	double				aspect;
	int					cur_cam;
	int					cam_count;
	struct s_image		img;
	struct s_ray		ray;
	struct s_res		res;
	struct s_ambient	ambient;
	struct s_element	*obj;
	struct s_element	*obj2;
	struct s_camera		*cam;
	struct s_list		*objs_list;
	struct s_list		*cam_list;
	struct s_list		*light_list;
}				t_mini_rt;

/*
** Parsing
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
int				check_split(char **split);
char			**free_split(char **split);
t_vec			split_vec(char *str, t_mini_rt *rt, int orient);
t_color			split_rgb(char *str, t_mini_rt *rt);
void			check_extension(t_mini_rt *rt, char *rt_file);


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
void			raytracing(t_mini_rt *rt);

/*
** Objects
*/
void			sphere(t_mini_rt *rt, t_element *sphere, t_vec ori, t_vec dir);
void			cylinder(t_mini_rt *rt, t_element *cylinder, t_vec ori,
					t_vec dir);
void			plane(t_mini_rt *rt, t_element *plane, t_vec ori, t_vec dir);
void			circle(t_mini_rt *rt, t_element *circle, t_vec ori, t_vec dir);
void			triangle(t_mini_rt *rt, t_element *triangle, t_vec ori,
					t_vec dir);
void			square(t_mini_rt *rt, t_element *plane, t_vec ori, t_vec dir);
void			create_circle(t_mini_rt *rt, t_element *cylinder, double t);

/*
** Camera
*/
void 			create_all_cam(t_mini_rt *rt);
void			select_cam(t_mini_rt *rt);
void			change_cam(t_mini_rt *rt);

/*
** Colors
*/
int				color_put(t_mini_rt *rt, int x, int y, int color);
t_color			color_average(t_color color1, t_color color2);
t_color			apply_lights(t_mini_rt *rt);
int				apply_shadows(t_mini_rt *rt, t_vec ori, t_vec dir);

/*
** Vectors
*/
t_vec			vec_add(t_vec v1, t_vec v2);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_mul(t_vec v1, double m);
t_vec			vec_div(t_vec v1, double d);
t_vec			vec_dot(t_vec v1, t_vec v2);
t_vec			vec_cross(t_vec v1, t_vec v2);
t_vec			vec_normalize(t_vec p);
double			vec_len(t_vec v);

/*
** Additional functions
*/
void			setup_rt(t_mini_rt *rt);
void			create_bmp_image(t_mini_rt *rt, char *file_name);

#endif
