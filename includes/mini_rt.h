/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 19:01:23 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "elements.h"
# include "keys.h"
# include "../libft/includes/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>

# define SPHERE 1
# define PLANE 2
# define SQUARE 3
# define CYLINDER 4
# define TRIANGLE 5
# define CIRCLE 6
# define CONE 7

# define THREAD_COUNT 16

# define BMP_FILE_NAME "img.bmp"
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40
# define BMP_HEADER_SIZE BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE

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
	float				intensity;
	float				t;
	float				k;
	float				aspect;
	int					cur_cam;
	int					cam_count;
	int					cur_obj;
	int					obj_count;
	int					cur_thr;
	float				anti_aliasing;
	int					sepia;
	struct s_color		tmp_color;
	struct s_image		img;
	struct s_ray		ray;
	struct s_res		res;
	struct s_ambient	ambient;
	struct s_element	*obj;
	struct s_element	*move_obj;
	struct s_camera		*cam;
	struct s_list		*objs_list;
	struct s_list		*cam_list;
	struct s_list		*light_list;
}				t_mini_rt;

typedef struct	s_thread
{
	int			cur_thr;
	t_mini_rt	scene;
}				t_thread;

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
int				parse_cone(t_mini_rt *rt);
int				parse_triangle(t_mini_rt *rt);
int				parse_antialiasing(t_mini_rt *rt);
int				check_split(char **split);
char			**free_split(char **split);
t_vec			split_vec(char *str, t_mini_rt *rt, int orient);
t_color			split_rgb(char *str, t_mini_rt *rt);
void			check_extension(t_mini_rt *rt, char *rt_file);
void			check_orient(t_vec *orient);
void			check_id(t_mini_rt *rt);

/*
** Events
*/
int				key_hook(int key, t_mini_rt *rt);
int				get_keypress(int key, t_mini_rt *rt);
int				handle_error(char *str, t_mini_rt *rt);
int				exit_and_free(t_mini_rt *rt);
void			free_element(void *elem);
void			redraw_window(t_mini_rt *rt);
t_element		*element_cpy(t_element *elem);
/*
** Raytracing functions
*/
void			raytracing(t_thread *th);
void			find_objs(t_mini_rt *rt, t_element *obj, t_vec ori, t_vec dir);
void			multi_thread(t_mini_rt *rt);
/*
** Objects
*/
void			sphere(t_mini_rt *rt, t_element *sphere, t_vec ori, t_vec dir);
void			cylinder(t_mini_rt *rt, t_element *cylinder, t_vec ori,
					t_vec dir);
void			cone(t_mini_rt *rt, t_element *cone, t_vec ori, t_vec dir);
void			plane(t_mini_rt *rt, t_element *plane, t_vec ori, t_vec dir);
void			circle(t_mini_rt *rt, t_element *circle, t_vec ori, t_vec dir);
void			triangle(t_mini_rt *rt, t_element *triangle, t_vec ori,
					t_vec dir);
void			square(t_mini_rt *rt, t_element *plane, t_vec ori, t_vec dir);
void			create_circle(t_mini_rt *rt, t_element *cylinder, float t);
void			select_objs(t_mini_rt *rt);
int				ft_obj_count(t_list *lst);
void			unselect_obj(t_mini_rt *rt);
/*
** Camera
*/
void			create_all_cam(t_mini_rt *rt);
void			select_cam(t_mini_rt *rt);
void			change_cam(t_mini_rt *rt);

/*
** Colors
*/
int				color_put(t_mini_rt *rt, int x, int y);
t_color			color_average(t_color color1, t_color color2);
t_color			color_add(t_color color1, t_color color2);
t_color			color_div(t_color color, int average);
t_color			apply_lights(t_mini_rt *rt);
int				apply_shadows(t_mini_rt *rt, t_vec ori, t_vec dir,
t_element *light);
void			apply_sepia(t_mini_rt *rt);

/*
** Vectors
*/
t_vec			vec_add(t_vec v1, t_vec v2);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_mul(t_vec v1, float m);
t_vec			vec_div(t_vec v1, float d);
t_vec			vec_dot(t_vec v1, t_vec v2);
t_vec			vec_cross(t_vec v1, t_vec v2);
t_vec			vec_normalize(t_vec p);
float			vec_len(t_vec v);
t_vec			vec_abs(t_vec v1);
t_vec			vec_reverse(t_vec v1);

/*
** Additional functions
*/
void			setup_rt(t_mini_rt *rt);
void			create_bmp_image(t_mini_rt *rt, char *file_name);

#endif
