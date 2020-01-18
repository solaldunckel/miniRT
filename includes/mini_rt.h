/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 09:29:00 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/18 07:07:40 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "elements.h"
# include "keys.h"
# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
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

# define DIFFUSE 10
# define DIRECTIONAL 11

# define THREAD_COUNT 16
# define MAX_REF 5

# define BMP_FILE_NAME "img.bmp"
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40

typedef struct	s_mini_rt
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					save;
	char				*line;
	char				**split;
	t_color				color;
	t_color				color2;
	float				intensity;
	float				t;
	t_vec				p;
	float				k;
	float				aspect;
	int					tr;
	int					nbref;
	int					cur_cam;
	int					cam_count;
	int					cur_obj;
	int					obj_count;
	int					cur_thr;
	int					percent;
	float				anti_aliasing;
	int					sepia;
	float				st;
	int					mouse;
	int					kb;
	t_color				tmp_color;
	t_image				img;
	t_ray				ray;
	t_res				res;
	t_ambient			ambient;
	t_element			*obj;
	t_element			*move_obj;
	t_camera			*cam;
	t_texture			*sky;
	t_list				*objs_list;
	t_list				*cam_list;
	t_list				*light_list;
}				t_mini_rt;

typedef struct	s_thread
{
	int					cur_thr;
	t_mini_rt			scene;
}				t_thread;

/*
** Parsing
*/
void			parse_rt_file(char *rt_file, t_mini_rt *rt);
void			parse_res(t_mini_rt *rt);
void			parse_ambient(t_mini_rt *rt);
void			parse_camera(t_mini_rt *rt);
void			parse_light(t_mini_rt *rt);
void			parse_sphere(t_mini_rt *rt);
void			parse_plane(t_mini_rt *rt);
void			parse_square(t_mini_rt *rt);
void			parse_cylindre(t_mini_rt *rt);
void			parse_cone(t_mini_rt *rt);
void			parse_triangle(t_mini_rt *rt);
void			parse_antialiasing(t_mini_rt *rt);
void			parse_dir_light(t_mini_rt *rt);
void			parse_cube(t_mini_rt *rt);
void			parse_sky(t_mini_rt *rt);
int				count_split(char **split);
int				check_split(char **split, int max);
char			**free_split(char **split);
t_vec			split_vec(char *str, t_mini_rt *rt, int orient);
t_color			split_rgb(char *str, t_mini_rt *rt);
int				check_orient(t_vec *orient);
void			check_id(t_mini_rt *rt);

/*
** Events
*/
int				key_hook(int key, t_mini_rt *rt);
int				get_mouse_pos(int x, int y, t_mini_rt *rt);
int				mouse_press(int button, int x, int y, t_mini_rt *rt);
int				mouse_release(int button, int x, int y, t_mini_rt *rt);
int				get_keypress(int key, t_mini_rt *rt);
void			handle_error(char *str, t_mini_rt *rt);
int				exit_and_free(t_mini_rt *rt);
void			free_element(void *elem);
void			redraw_window(t_mini_rt *rt);
t_element		*element_cpy(t_element *elem, t_mini_rt *rt);

/*
** Raytracing functions
*/
void			raytracing(t_thread *th);
void			find_objs(t_mini_rt *rt, t_element *obj, t_vec ori, t_vec dir);
void			multi_thread(t_mini_rt *rt);
t_color			ray_intersect(t_mini_rt *rt);

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
void			create_circle(t_mini_rt *rt, t_element *cylinder, float t,
					int create);
void			create_square(t_mini_rt *rt, t_element *cube, t_vec point,
					t_vec orient);
void			select_objs(t_mini_rt *rt);
int				objs_count(t_list *lst);
void			unselect_obj(t_mini_rt *rt);
void			create_texture(t_mini_rt *rt, t_element *elem, char *file_path);

/*
** Camera
*/
void			create_all_cam(t_mini_rt *rt);
void			select_cam(t_mini_rt *rt);
void			change_cam(t_mini_rt *rt);

/*
** Colors
*/
void			color_put(t_mini_rt *rt, int x, int y);
t_color			color_average(t_color color1, t_color color2);
t_color			color_add(t_color color1, t_color color2, int cap);
t_color			color_div(t_color color, int average);
t_color			apply_lights(t_mini_rt *rt);
int				apply_shadows(t_mini_rt *rt, t_vec ori, t_vec dir,
					t_element *light);
void			apply_sepia(t_mini_rt *rt);
t_color			get_color(t_mini_rt *rt);
void			get_tex_coord(t_mini_rt *rt, t_element *sphere, int *column,
					int *row);
void			reflect(t_mini_rt *rt);
t_color			apply_intensity(float intensity, t_color color);
t_color			get_sky_coord(t_mini_rt *rt);

/*
** Vectors
*/
t_vec			vec_add(t_vec v1, t_vec v2);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_mul(t_vec v1, float m);
t_vec			vec_div(t_vec v1, float d);
float			vec_dot(t_vec v1, t_vec v2);
t_vec			vec_cross(t_vec v1, t_vec v2);
t_vec			vec_normalize(t_vec p);
float			vec_len(t_vec v);
t_vec			get_normal_vector(t_mini_rt *rt, t_vec p);

/*
** Additional functions
*/
void			setup_rt(t_mini_rt *rt);
void			show_keybind(t_mini_rt *rt);
void			create_bmp_image(t_mini_rt *rt, char *file_name);
t_texture		create_sky(t_mini_rt *rt, char *file_path);
void			free_sky(t_mini_rt *rt);
void			progress_bar(t_thread *thread);

#endif
