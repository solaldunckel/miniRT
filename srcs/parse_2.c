/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/09 15:03:07 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sphere(t_mini_rt *rt)
{
	t_element		*sphere;

	if (!(sphere = ft_calloc(1, sizeof(t_element))))
		return (0);
	sphere->id = ft_strdup(SPHERE);
	sphere->point.x = ft_atof_rt(rt->line, rt);
	sphere->point.y = ft_atof_rt(rt->line, rt);
	sphere->point.z = ft_atof_rt(rt->line, rt);
	sphere->diameter = ft_atof_rt(rt->line, rt);
	sphere->color.r = ft_atoi_rt(rt->line, rt);
	sphere->color.g = ft_atoi_rt(rt->line, rt);
	sphere->color.b = ft_atoi_rt(rt->line, rt);
	ft_lstadd_back(&rt->list, ft_lstnew(sphere));
	if (DEBUG_PARSING)
		printf("sphere		point : %.f,%.f,%.f 		diameter : %.1f 	rgb : %d,%d,%d\n",
		sphere->point.x, sphere->point.y, sphere->point.z, sphere->diameter,
		sphere->color.r, sphere->color.g, sphere->color.b);
	return (1);
}

int		parse_plane(t_mini_rt *rt)
{
	t_element		*plane;

	if (!(plane = ft_calloc(1, sizeof(t_element))))
		return (0);
	plane->id = ft_strdup(PLANE);
	plane->point.x = ft_atof_rt(rt->line, rt);
	plane->point.y = ft_atof_rt(rt->line, rt);
	plane->point.z = ft_atof_rt(rt->line, rt);
	plane->orient.x = ft_atof_rt(rt->line, rt);
	plane->orient.y = ft_atof_rt(rt->line, rt);
	plane->orient.z = ft_atof_rt(rt->line, rt);
	plane->color.r = ft_atoi_rt(rt->line, rt);
	plane->color.g = ft_atoi_rt(rt->line, rt);
	plane->color.b = ft_atoi_rt(rt->line, rt);
	ft_lstadd_back(&rt->list, ft_lstnew(plane));
	if (DEBUG_PARSING)
		printf("plane		point : %.f,%.f,%.f 		orient : %.f,%.f,%.f 		rgb : %d,%d,%d\n",
		plane->point.x, plane->point.y, plane->point.z,
		plane->orient.x, plane->orient.y, plane->orient.z,
		plane->color.r, plane->color.g, plane->color.b);
	return (1);
}

int		parse_square(t_mini_rt *rt)
{
	t_element		*square;

	if (!(square = ft_calloc(1, sizeof(t_element))))
		return (0);
	square->id = ft_strdup(SQUARE);
	square->point.x = ft_atof_rt(rt->line, rt);
	square->point.y = ft_atof_rt(rt->line, rt);
	square->point.z = ft_atof_rt(rt->line, rt);
	square->orient.x = ft_atof_rt(rt->line, rt);
	square->orient.y = ft_atof_rt(rt->line, rt);
	square->orient.z = ft_atof_rt(rt->line, rt);
	square->height = ft_atof_rt(rt->line, rt);
	square->color.r = ft_atoi_rt(rt->line, rt);
	square->color.g = ft_atoi_rt(rt->line, rt);
	square->color.b = ft_atoi_rt(rt->line, rt);
	ft_lstadd_back(&rt->list, ft_lstnew(square));
	if (DEBUG_PARSING)
		printf("square		point : %.f,%.f,%.f 	orient : %.f,%.f,%.f 		height : %.1f 			rgb : %d,%d,%d\n",
		square->point.x, square->point.y, square->point.z,
		square->orient.x, square->orient.y, square->orient.z, square->height,
		square->color.r, square->color.g, square->color.b);
	return (1);
}

int		parse_cylindre(t_mini_rt *rt)
{
	t_element		*cylinder;

	if (!(cylinder = ft_calloc(1, sizeof(t_element))))
		return (0);
	cylinder->id = ft_strdup(CYLINDER);
	cylinder->point.x = ft_atof_rt(rt->line, rt);
	cylinder->point.y = ft_atof_rt(rt->line, rt);
	cylinder->point.z = ft_atof_rt(rt->line, rt);
	cylinder->orient.x = ft_atof_rt(rt->line, rt);
	cylinder->orient.y = ft_atof_rt(rt->line, rt);
	cylinder->orient.z = ft_atof_rt(rt->line, rt);
	cylinder->diameter = ft_atof_rt(rt->line, rt);
	cylinder->height = ft_atof_rt(rt->line, rt);
	cylinder->color.r = ft_atoi_rt(rt->line, rt);
	cylinder->color.g = ft_atoi_rt(rt->line, rt);
	cylinder->color.b = ft_atoi_rt(rt->line, rt);
	ft_lstadd_back(&rt->list, ft_lstnew(cylinder));
	if (DEBUG_PARSING)
		printf("cylinder	point : %.f,%.f,%.f 	orient : %.f,%.f,%.f 		diameter : %.1f 		height : %.1f 		rgb : %d,%d,%d\n",
		cylinder->point.x, cylinder->point.y, cylinder->point.z,
		cylinder->orient.x, cylinder->orient.y, cylinder->orient.z, cylinder->diameter, cylinder->height,
		cylinder->color.r, cylinder->color.g, cylinder->color.b);
	return (1);
}

int		parse_triangle(t_mini_rt *rt)
{
	t_element		*triangle;

	if (!(triangle = ft_calloc(1, sizeof(t_element))))
		return (0);
	triangle->id = ft_strdup(TRIANGLE);
	triangle->point.x = ft_atof_rt(rt->line, rt);
	triangle->point.y = ft_atof_rt(rt->line, rt);
	triangle->point.z = ft_atof_rt(rt->line, rt);
	triangle->point2.x = ft_atof_rt(rt->line, rt);
	triangle->point2.y = ft_atof_rt(rt->line, rt);
	triangle->point2.z = ft_atof_rt(rt->line, rt);
	triangle->point3.x = ft_atof_rt(rt->line, rt);
	triangle->point3.y = ft_atof_rt(rt->line, rt);
	triangle->point3.z = ft_atof_rt(rt->line, rt);
	triangle->color.r = ft_atoi_rt(rt->line, rt);
	triangle->color.g = ft_atoi_rt(rt->line, rt);
	triangle->color.b = ft_atoi_rt(rt->line, rt);
	ft_lstadd_back(&rt->list, ft_lstnew(triangle));
	if (DEBUG_PARSING)
		printf("triangle	point1 : %.f,%.f,%.f 	point2 : %.f,%.f,%.f 	point3 : %.f,%.f,%.f 		rgb : %d,%d,%d\n",
		triangle->point.x, triangle->point.y, triangle->point.z,
		triangle->point2.x, triangle->point2.y, triangle->point2.z,
		triangle->point3.x, triangle->point3.y, triangle->point3.z,
		triangle->color.r, triangle->color.g, triangle->color.b);
	return (1);
}
