/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/07 13:46:37 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_res(t_mini_rt *rt)
{
	rt->res.x = ft_atoi_rt(rt->line, rt);
	rt->res.y = ft_atoi_rt(rt->line, rt);
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
	camera->id = ft_strdup("camera");
	camera->pov.x = ft_atof_rt(rt->line, rt);
	camera->pov.y = ft_atof_rt(rt->line, rt);
	camera->pov.z = ft_atof_rt(rt->line, rt);
	camera->orient.x = ft_atof_rt(rt->line, rt);
	camera->orient.y = ft_atof_rt(rt->line, rt);
	camera->orient.z = ft_atof_rt(rt->line, rt);
	ft_lstadd_back(&rt->list, ft_lstnew(camera));
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
	light->id = ft_strdup("light");
	light->point.x = ft_atof_rt(rt->line, rt);
	light->point.y = ft_atof_rt(rt->line, rt);
	light->point.z = ft_atof_rt(rt->line, rt);
	light->ratio = ft_atof_rt(rt->line, rt);
	light->color.r = ft_atoi_rt(rt->line, rt);
	light->color.g = ft_atoi_rt(rt->line, rt);
	light->color.b = ft_atoi_rt(rt->line, rt);
	ft_lstadd_back(&rt->list, ft_lstnew(light));
	if (DEBUG_PARSING)
		printf("light		point : %.f,%.f,%.f 	ratio : %.1f 		rgb : %d,%d,%d\n",
		light->point.x, light->point.y, light->point.z, light->ratio,
		light->color.r, light->color.g, light->color.b);
	return (1);
}
