/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 12:32:37 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_res(t_mini_rt *rt, char *line)
{
	rt->i++;
	rt->res.x = ft_atoi_rt(line, rt);
	rt->res.y = ft_atoi_rt(line, rt);
	printf("resolution 	x : %d y : %d\n", rt->res.x, rt->res.y);
	return (1);
}

int		parse_ambient(t_mini_rt *rt, char *line)
{
	rt->i++;
	rt->ambient.ratio = ft_atof_rt(line, rt);
	rt->ambient.r = ft_atoi_rt(line, rt);
	rt->i++;
	rt->ambient.g = ft_atoi_rt(line, rt);
	rt->i++;
	rt->ambient.b = ft_atoi_rt(line, rt);
	printf("ambient 	ratio : %.1f rgb : %d,%d,%d\n", rt->ambient.ratio,
	rt->ambient.r, rt->ambient.g, rt->ambient.b);
	return (1);
}

int		parse_camera(t_mini_rt *rt, char *line)
{
	rt->i++;
	rt->camera.pov_x = ft_atof_rt(line, rt);
	rt->i++;
	rt->camera.pov_y = ft_atof_rt(line, rt);
	rt->i++;
	rt->camera.pov_z = ft_atof_rt(line, rt);

	rt->camera.orient_x = ft_atof_rt(line, rt);
	rt->i++;
	rt->camera.orient_y = ft_atof_rt(line, rt);
	rt->i++;
	rt->camera.orient_z = ft_atof_rt(line, rt);
	printf("camera 		pov xyz %.f,%.f,%.f orient xyz %.f,%.f,%.f\n",
		rt->camera.pov_x, rt->camera.pov_y, rt->camera.pov_z,
		rt->camera.orient_x, rt->camera.orient_y, rt->camera.orient_z);
	return (1);
}

int		parse_light(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("light\n");
	return (1);
}
