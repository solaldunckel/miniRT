/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 12:03:06 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_rt_file(char *rt_file, t_mini_rt *rt)
{
	int		fd;

	if ((fd = open(rt_file, O_RDONLY)) < 0)
		handle_error("fail to open scene file", rt);
	while (get_next_line(fd, &rt->line) > 0)
	{
		rt->split = ft_split(rt->line, ' ');
		ft_strequ(rt->split[0], "R") ? parse_res(rt) : 0;
		ft_strequ(rt->split[0], "A") ? parse_ambient(rt) : 0;
		ft_strequ(rt->split[0], "c") ? parse_camera(rt) : 0;
		ft_strequ(rt->split[0], "l") ? parse_light(rt) : 0;
		ft_strequ(rt->split[0], "sp") ? parse_sphere(rt) : 0;
		ft_strequ(rt->split[0], "pl") ? parse_plane(rt) : 0;
		ft_strequ(rt->split[0], "sq") ? parse_square(rt) : 0;
		ft_strequ(rt->split[0], "cy") ? parse_cylindre(rt) : 0;
		ft_strequ(rt->split[0], "tr") ? parse_triangle(rt) : 0;
		free_split(rt->split);
		ft_strdel(&rt->line);
	}
	if (!(rt->cam_count = ft_lstsize(rt->cam_list)))
		handle_error("no camera available", rt);
}

int		parse_res(t_mini_rt *rt)
{
	if (check_split(rt) != 3)
		handle_error("invalid resolution", rt);
	rt->res.x = ft_atoi(rt->split[1]);
	rt->res.y = ft_atoi(rt->split[2]);
	if (rt->res.x < 1 || rt->res.y < 1)
		handle_error("resolution too small", rt);
	rt->res.x > 2560 ? rt->res.x = 2560 : 0;
	rt->res.y > 1440 ? rt->res.y = 1440 : 0;
	if (DEBUG_PARSING)
		printf("resolution 	x : %d 		y : %d\n", rt->res.x, rt->res.y);
	return (1);
}

int		parse_ambient(t_mini_rt *rt)
{
	if (check_split(rt) != 3)
		handle_error("invalid ambient light", rt);
	rt->ambient.ratio = ft_atof(rt->split[1]);
	rt->ambient.color = split_rgb(rt->split[2], rt);
	if (DEBUG_PARSING)
		printf("ambient 	ratio : %.1f 		rgb : %d,%d,%d\n", rt->ambient.ratio,
		rt->ambient.color.r, rt->ambient.color.g, rt->ambient.color.b);
	return (1);
}

int		parse_camera(t_mini_rt *rt)
{
	t_element		*camera;

	if (!(camera = ft_calloc(1, sizeof(t_element))))
		return (0);
	if (check_split(rt) != 3)
	{
		free(camera);
		return (0);
	}
	camera->id = ft_strdup(CAMERA);
	camera->pov = split_vec(rt->split[1], rt);
	camera->orient = split_vec(rt->split[2], rt);
	ft_lstadd_back(&rt->cam_list, ft_lstnew(camera));
	if (DEBUG_PARSING)
		printf("camera 		pov : %.f,%.f,%.f 		orient : %.f,%.f,%.f\n",
		camera->pov.x, camera->pov.y, camera->pov.z,
		camera->orient.x, camera->orient.y, camera->orient.z);
	return (1);
}

int		parse_light(t_mini_rt *rt)
{
	t_element		*light;

	if (!(light = ft_calloc(1, sizeof(t_element))))
		return (0);
	if (check_split(rt) != 4)
	{
		free(light);
		return (0);
	}
	light->id = ft_strdup(LIGHT);
	light->point = split_vec(rt->split[1], rt);
	light->ratio = ft_atof(rt->split[2]);
	light->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->light_list, ft_lstnew(light));
	if (DEBUG_PARSING)
		printf("light		point : %.f,%.f,%.f 	ratio : %.1f 		rgb : %d,%d,%d\n",
		light->point.x, light->point.y, light->point.z, light->ratio,
		light->color.r, light->color.g, light->color.b);
	return (1);
}
