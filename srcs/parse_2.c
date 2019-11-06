/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 17:19:31 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sphere(t_mini_rt *rt, char *line)
{
	rt->sphere.point.x = ft_atof_rt(line, rt);
	rt->sphere.point.y = ft_atof_rt(line, rt);
	rt->sphere.point.z = ft_atof_rt(line, rt);
	rt->sphere.diameter = ft_atof_rt(line, rt);
	rt->sphere.color.r = ft_atoi_rt(line, rt);
	rt->sphere.color.g = ft_atoi_rt(line, rt);
	rt->sphere.color.b = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("sphere		point : %.f,%.f,%.f 		diameter : %.1f 	rgb : %d,%d,%d\n",
		rt->sphere.point.x, rt->sphere.point.y, rt->sphere.point.z, rt->sphere.diameter,
		rt->sphere.color.r, rt->sphere.color.g, rt->sphere.color.b);
	return (1);
}

int		parse_plane(t_mini_rt *rt, char *line)
{
	rt->plane.point.x = ft_atof_rt(line, rt);
	rt->plane.point.y = ft_atof_rt(line, rt);
	rt->plane.point.z = ft_atof_rt(line, rt);
	rt->plane.orient.x = ft_atof_rt(line, rt);
	rt->plane.orient.y = ft_atof_rt(line, rt);
	rt->plane.orient.z = ft_atof_rt(line, rt);
	rt->plane.color.r = ft_atoi_rt(line, rt);
	rt->plane.color.g = ft_atoi_rt(line, rt);
	rt->plane.color.b = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("plane		point : %.f,%.f,%.f 		orient : %.f,%.f,%.f 		rgb : %d,%d,%d\n",
		rt->plane.point.x, rt->plane.point.y, rt->plane.point.z,
		rt->plane.orient.x, rt->plane.orient.y, rt->plane.orient.z,
		rt->plane.color.r, rt->plane.color.g, rt->plane.color.b);
	return (1);
}

int		parse_square(t_mini_rt *rt, char *line)
{
	rt->square.point.x = ft_atof_rt(line, rt);
	rt->square.point.y = ft_atof_rt(line, rt);
	rt->square.point.z = ft_atof_rt(line, rt);
	rt->square.orient.x = ft_atof_rt(line, rt);
	rt->square.orient.y = ft_atof_rt(line, rt);
	rt->square.orient.z = ft_atof_rt(line, rt);
	rt->square.height = ft_atof_rt(line, rt);
	rt->square.color.r = ft_atoi_rt(line, rt);
	rt->square.color.g = ft_atoi_rt(line, rt);
	rt->square.color.b = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("square		point : %.f,%.f,%.f 	orient : %.f,%.f,%.f 		height : %.1f 			rgb : %d,%d,%d\n",
		rt->square.point.x, rt->square.point.y, rt->square.point.z,
		rt->square.orient.x, rt->square.orient.y, rt->square.orient.z, rt->square.height,
		rt->square.color.r, rt->square.color.g, rt->square.color.b);
	return (1);
}

int		parse_cylindre(t_mini_rt *rt, char *line)
{
	rt->cylinder.point.x = ft_atof_rt(line, rt);
	rt->cylinder.point.y = ft_atof_rt(line, rt);
	rt->cylinder.point.z = ft_atof_rt(line, rt);
	rt->cylinder.orient.x = ft_atof_rt(line, rt);
	rt->cylinder.orient.y = ft_atof_rt(line, rt);
	rt->cylinder.orient.z = ft_atof_rt(line, rt);
	rt->cylinder.diameter = ft_atof_rt(line, rt);
	rt->cylinder.height = ft_atof_rt(line, rt);
	rt->cylinder.color.r = ft_atoi_rt(line, rt);
	rt->cylinder.color.g = ft_atoi_rt(line, rt);
	rt->cylinder.color.b = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("cylinder	point : %.f,%.f,%.f 	orient : %.f,%.f,%.f 		diameter : %.1f 		height : %.1f 		rgb : %d,%d,%d\n",
		rt->cylinder.point.x, rt->cylinder.point.y, rt->cylinder.point.z,
		rt->cylinder.orient.x, rt->cylinder.orient.y, rt->cylinder.orient.z, rt->cylinder.diameter, rt->cylinder.height,
		rt->cylinder.color.r, rt->cylinder.color.g, rt->cylinder.color.b);
	return (1);
}

int		parse_triangle(t_mini_rt *rt, char *line)
{
	rt->triangle.point1.x = ft_atof_rt(line, rt);
	rt->triangle.point1.y = ft_atof_rt(line, rt);
	rt->triangle.point1.z = ft_atof_rt(line, rt);
	rt->triangle.point2.x = ft_atof_rt(line, rt);
	rt->triangle.point2.y = ft_atof_rt(line, rt);
	rt->triangle.point2.z = ft_atof_rt(line, rt);
	rt->triangle.point3.x = ft_atof_rt(line, rt);
	rt->triangle.point3.y = ft_atof_rt(line, rt);
	rt->triangle.point3.z = ft_atof_rt(line, rt);
	rt->triangle.color.r = ft_atoi_rt(line, rt);
	rt->triangle.color.g = ft_atoi_rt(line, rt);
	rt->triangle.color.b = ft_atoi_rt(line, rt);
	if (DEBUG_PARSING)
		printf("triangle	point1 : %.f,%.f,%.f 	point2 : %.f,%.f,%.f 	point3 : %.f,%.f,%.f 		rgb : %d,%d,%d\n",
		rt->triangle.point1.x, rt->triangle.point1.y, rt->triangle.point1.z,
		rt->triangle.point2.x, rt->triangle.point2.y, rt->triangle.point2.z,
		rt->triangle.point3.x, rt->triangle.point3.y, rt->triangle.point3.z,
		rt->triangle.color.r, rt->triangle.color.g, rt->triangle.color.b);
	return (1);
}
