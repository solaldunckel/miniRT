/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/10 18:14:04 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_rt_file(char *rt_file, t_mini_rt *rt)
{
	int		fd;

	if ((fd = open(rt_file, O_RDONLY)) < 0)
		handle_error("fail to open scene file", rt);
	while (get_next_line(fd, &rt->line) > 0)
	{
		rt->i = 0;
		while (!ft_isalpha(rt->line[rt->i]))
			rt->i++;
		ft_strstr_rt(&rt->line[rt->i], "R", rt) ? parse_res(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "A", rt) ? parse_ambient(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "c", rt) ? parse_camera(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "l", rt) ? parse_light(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "sp", rt) ? parse_sphere(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "pl", rt) ? parse_plane(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "sq", rt) ? parse_square(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "cy", rt) ? parse_cylindre(rt) : 0;
		ft_strstr_rt(&rt->line[rt->i], "tr", rt) ? parse_triangle(rt) : 0;
		ft_strdel(&rt->line);
	}
	return (1);
}

int		parse_res(t_mini_rt *rt)
{
	rt->res.x = ft_atoi_rt(rt->line, rt);
	rt->res.y = ft_atoi_rt(rt->line, rt);
	if (rt->res.x < 1 || rt->res.y < 1)
		handle_error("resolution too small", rt);
	if (rt->res.x > 2560)
		rt->res.x = 2560;
	if (rt->res.y > 1440)
		rt->res.y = 1440;
	if (DEBUG_PARSING)
		printf("resolution 	x : %d 		y : %d\n", rt->res.x, rt->res.y);
	return (1);
}

int		parse_ambient(t_mini_rt *rt)
{
	rt->ambient.ratio = ft_atof_rt(rt->line, rt);
	rt->ambient.color.r = ft_atoi_rt(rt->line, rt);
	rt->ambient.color.g = ft_atoi_rt(rt->line, rt);
	rt->ambient.color.b = ft_atoi_rt(rt->line, rt);
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
	camera->id = ft_strdup(CAMERA);
	camera->pov.x = ft_atof_rt(rt->line, rt);
	camera->pov.y = ft_atof_rt(rt->line, rt);
	camera->pov.z = ft_atof_rt(rt->line, rt);
	camera->orient.x = ft_atof_rt(rt->line, rt);
	camera->orient.y = ft_atof_rt(rt->line, rt);
	camera->orient.z = ft_atof_rt(rt->line, rt);
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
	light->id = ft_strdup(LIGHT);
	light->point.x = ft_atof_rt(rt->line, rt);
	light->point.y = ft_atof_rt(rt->line, rt);
	light->point.z = ft_atof_rt(rt->line, rt);
	light->ratio = ft_atof_rt(rt->line, rt);
	light->color.r = ft_atoi_rt(rt->line, rt);
	light->color.g = ft_atoi_rt(rt->line, rt);
	light->color.b = ft_atoi_rt(rt->line, rt);
	ft_lstadd_back(&rt->light_list, ft_lstnew(light));
	if (DEBUG_PARSING)
		printf("light		point : %.f,%.f,%.f 	ratio : %.1f 		rgb : %d,%d,%d\n",
		light->point.x, light->point.y, light->point.z, light->ratio,
		light->color.r, light->color.g, light->color.b);
	return (1);
}
