/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/12 13:58:36 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sphere(t_mini_rt *rt)
{
	t_element		*sphere;

	if (!(sphere = ft_calloc(1, sizeof(t_element))))
		return (0);
	if (check_split(rt->split) != 4)
	{
		free(sphere);
		handle_error("sphere parsing error", rt);
	}
	sphere->id = ft_strdup(SPHERE);
	sphere->point = split_vec(rt->split[1], rt);
	sphere->diameter = ft_atof(rt->split[2]);
	sphere->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(sphere));
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
	if (check_split(rt->split) != 4)
	{
		free(plane);
		handle_error("plane parsing error", rt);
	}
	plane->id = ft_strdup(PLANE);
	plane->point = split_vec(rt->split[1], rt);
	plane->orient = split_vec(rt->split[2], rt);
	plane->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(plane));
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
	if (check_split(rt->split) != 5)
	{
		free(square);
		handle_error("square parsing error", rt);
	}
	square->id = ft_strdup(SQUARE);
	square->point = split_vec(rt->split[1], rt);
	square->orient = split_vec(rt->split[2], rt);
	square->height = ft_atof(rt->split[3]);
	square->color = split_rgb(rt->split[4], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(square));
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
	if (check_split(rt->split) != 6)
	{
		free(cylinder);
		handle_error("cylinder parsing error", rt);
	}
	cylinder->id = ft_strdup(CYLINDER);
	cylinder->point = split_vec(rt->split[1], rt);
	cylinder->orient = split_vec(rt->split[2], rt);
	cylinder->diameter = ft_atof(rt->split[3]);
	cylinder->height = ft_atof(rt->split[4]);
	cylinder->color = split_rgb(rt->split[5], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(cylinder));
	if (DEBUG_PARSING)
		printf("cylinder	point : %.1f,%.1f,%.1f 	orient : %.f,%.f,%.f 		diameter : %.1f 		height : %.2f 		rgb : %d,%d,%d\n",
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
	if (check_split(rt->split) != 5)
	{
		free(triangle);
		handle_error("triangle parsing error", rt);
	}
	triangle->id = ft_strdup(TRIANGLE);
	triangle->point = split_vec(rt->split[1], rt);
	triangle->point2 = split_vec(rt->split[2], rt);
	triangle->point3 = split_vec(rt->split[3], rt);
	triangle->color = split_rgb(rt->split[4], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(triangle));
	if (DEBUG_PARSING)
		printf("triangle	point1 : %.f,%.f,%.f 	point2 : %.f,%.f,%.f 	point3 : %.f,%.f,%.f 		rgb : %d,%d,%d\n",
		triangle->point.x, triangle->point.y, triangle->point.z,
		triangle->point2.x, triangle->point2.y, triangle->point2.z,
		triangle->point3.x, triangle->point3.y, triangle->point3.z,
		triangle->color.r, triangle->color.g, triangle->color.b);
	return (1);
}
