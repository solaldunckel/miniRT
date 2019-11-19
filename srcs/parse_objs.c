/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/19 11:15:17 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sphere(t_mini_rt *rt)
{
	t_element		*sphere;

	if (!(sphere = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 4)
	{
		free(sphere);
		handle_error("sphere parsing error", rt);
	}
	sphere->id = 1;
	sphere->point = split_vec(rt->split[1], rt, 0);
	sphere->diameter = ft_atof(rt->split[2]);
	sphere->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(sphere));
	if (sphere->diameter < 0)
		handle_error("sphere parsing error", rt);
	return (1);
}

int		parse_plane(t_mini_rt *rt)
{
	t_element		*plane;

	if (!(plane = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 4)
	{
		free(plane);
		handle_error("plane parsing error", rt);
	}
	plane->id = 2;
	plane->point = split_vec(rt->split[1], rt, 0);
	plane->orient = split_vec(rt->split[2], rt, 1);
	plane->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(plane));
	return (1);
}

int		parse_square(t_mini_rt *rt)
{
	t_element		*square;

	if (!(square = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 5)
	{
		free(square);
		handle_error("square parsing error", rt);
	}
	square->id = 3;
	square->point = split_vec(rt->split[1], rt, 0);
	square->orient = split_vec(rt->split[2], rt, 1);
	square->height = ft_atof(rt->split[3]);
	square->color = split_rgb(rt->split[4], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(square));
	if (square->height < 0)
		handle_error("square parsing error", rt);
	return (1);
}

int		parse_cylindre(t_mini_rt *rt)
{
	t_element		*cylinder;

	if (!(cylinder = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 6)
	{
		free(cylinder);
		handle_error("cylinder parsing error", rt);
	}
	cylinder->id = 4;
	cylinder->point = split_vec(rt->split[1], rt, 0);
	cylinder->orient = split_vec(rt->split[2], rt, 1);
	cylinder->diameter = ft_atof(rt->split[3]);
	cylinder->height = ft_atof(rt->split[4]);
	cylinder->color = split_rgb(rt->split[5], rt);
	ft_lstadd_back(&rt->objs_list, ft_lstnew(cylinder));
	if (cylinder->height < 0 || cylinder->diameter < 0)
		handle_error("square parsing error", rt);
	create_circle(rt, cylinder, cylinder->height / 2);
	create_circle(rt, cylinder, cylinder->height / -2);
	return (1);
}

int		parse_triangle(t_mini_rt *rt)
{
	t_element		*triangle;

	if (!(triangle = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 5)
	{
		free(triangle);
		handle_error("triangle parsing error", rt);
	}
	triangle->id = 5;
	triangle->point = split_vec(rt->split[1], rt, 0);
	triangle->point2 = split_vec(rt->split[2], rt, 0);
	triangle->point3 = split_vec(rt->split[3], rt, 0);
	triangle->color = split_rgb(rt->split[4], rt);
	triangle->orient = vec_normalize(vec_cross(
		vec_sub(triangle->point2, triangle->point),
		vec_sub(triangle->point3, triangle->point)));
	ft_lstadd_back(&rt->objs_list, ft_lstnew(triangle));
	return (1);
}
