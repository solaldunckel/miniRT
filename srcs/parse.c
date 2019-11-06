/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 17:18:56 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_res(t_mini_rt *rt, char *line)
{
	rt->res.x = ft_atoi_rt(line, rt);
	rt->res.y = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("resolution 	x : %d 		y : %d\n", rt->res.x, rt->res.y);
	return (1);
}

int		parse_ambient(t_mini_rt *rt, char *line)
{
	rt->ambient.ratio = ft_atof_rt(line, rt);
	rt->ambient.color.r = ft_atoi_rt(line, rt);
	rt->ambient.color.g = ft_atoi_rt(line, rt);
	rt->ambient.color.b = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("ambient 	ratio : %.1f 		rgb : %d,%d,%d\n", rt->ambient.ratio,
		rt->ambient.color.r, rt->ambient.color.g, rt->ambient.color.b);
	return (1);
}

int		parse_camera(t_mini_rt *rt, char *line)
{
	rt->camera.pov.x = ft_atof_rt(line, rt);
	rt->camera.pov.y = ft_atof_rt(line, rt);
	rt->camera.pov.z = ft_atof_rt(line, rt);
	rt->camera.orient.x = ft_atof_rt(line, rt);
	rt->camera.orient.y = ft_atof_rt(line, rt);
	rt->camera.orient.z = ft_atof_rt(line, rt);
	if (DEBUG_PARSING)
		printf("camera 		pov : %.f,%.f,%.f 		orient : %.f,%.f,%.f\n",
		rt->camera.pov.x, rt->camera.pov.y, rt->camera.pov.z,
		rt->camera.orient.x, rt->camera.orient.y, rt->camera.orient.z);
	return (1);
}

int		parse_light(t_mini_rt *rt, char *line)
{
	rt->light.point.x = ft_atof_rt(line, rt);
	rt->light.point.y = ft_atof_rt(line, rt);
	rt->light.point.z = ft_atof_rt(line, rt);
	rt->light.ratio = ft_atof_rt(line, rt);
	rt->light.color.r = ft_atoi_rt(line, rt);
	rt->light.color.g = ft_atoi_rt(line, rt);
	rt->light.color.b = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("light		point : %.f,%.f,%.f 	ratio : %.1f 		rgb : %d,%d,%d\n",
		rt->light.point.x, rt->light.point.y, rt->light.point.z, rt->light.ratio,
		rt->light.color.r, rt->light.color.g, rt->light.color.b);
	return (1);
}
