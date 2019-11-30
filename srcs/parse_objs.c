/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/30 21:50:50 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sphere(t_mini_rt *rt)
{
	t_element	*sphere;
	int			check;

	check = check_split(rt->split);
	if (!(sphere = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if ((sphere->id = 1) == 1 && (check > 5 || check < 4))
	{
		if (!ft_str_end(rt->split[3], ".xpm"))
		{
			free(sphere);
			handle_error("sphere parsing error", rt);
		}
		check = 5;
	}
	sphere->point = split_vec(rt->split[1], rt, 0);
	sphere->diameter = ft_atof(rt->split[2]);
	if ((sphere->ref = 0) == 0 && ft_str_end(rt->split[3], ".xpm"))
		create_texture(rt, sphere, rt->split[3]);
	else
		sphere->color = split_rgb(rt->split[3], rt);
	rt->split[4] ? sphere->ref = ft_atof(rt->split[4]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(sphere));
	sphere->diameter < 0 ? handle_error("sphere parsing error", rt) : 0;
	return (1);
}

int		parse_plane(t_mini_rt *rt)
{
	t_element	*plane;
	int			check;

	check = check_split(rt->split);
	if (!(plane = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if ((check < 4 || check > 5) && check != 0 && !rt->split[1])
	{
		free(plane);
		handle_error("plane parsing error", rt);
	}
	plane->id = 2;
	plane->point = split_vec(rt->split[1], rt, 0);
	plane->orient = split_vec(rt->split[2], rt, 1);
	plane->color = split_rgb(rt->split[3], rt);
	plane->ref = 0;
	rt->split[4] ? plane->ref = ft_atof(rt->split[4]) : 0;
	if (rt->split[5] && ft_strequ(rt->split[5], "raiiinbow"))
		plane->rainbow = 1;
	if (rt->split[4] && ft_strequ(rt->split[4], "raiiinbow"))
		plane->rainbow = 1;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(plane));
	return (1);
}

int		parse_square(t_mini_rt *rt)
{
	t_element	*square;
	int			check;

	check = check_split(rt->split);
	if (!(square = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check < 5 || check > 6)
	{
		free(square);
		handle_error("square parsing error", rt);
	}
	square->id = 3;
	square->point = split_vec(rt->split[1], rt, 0);
	square->orient = split_vec(rt->split[2], rt, 1);
	square->height = ft_atof(rt->split[3]);
	square->color = split_rgb(rt->split[4], rt);
	square->ref = 0;
	check == 6 ? square->ref = ft_atof(rt->split[5]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(square));
	if (square->height < 0)
		handle_error("square parsing error", rt);
	return (1);
}

int		parse_cylindre(t_mini_rt *rt)
{
	t_element	*cylinder;
	int			check;

	check = check_split(rt->split);
	if (!(cylinder = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if ((cylinder->ref = 0) == 0 && (check < 6 || check > 7))
	{
		free(cylinder);
		handle_error("cylinder parsing error", rt);
	}
	cylinder->id = 4;
	cylinder->point = split_vec(rt->split[1], rt, 0);
	cylinder->orient = split_vec(rt->split[2], rt, 1);
	cylinder->orient = vec_normalize(cylinder->orient);
	cylinder->diameter = ft_atof(rt->split[3]);
	cylinder->height = ft_atof(rt->split[4]);
	cylinder->color = split_rgb(rt->split[5], rt);
	check == 7 ? cylinder->ref = ft_atof(rt->split[6]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(cylinder));
	if (cylinder->height < 0 || cylinder->diameter < 0)
		handle_error("cylinder parsing error", rt);
	create_circle(rt, cylinder, cylinder->height / 2);
	create_circle(rt, cylinder, cylinder->height / -2);
	return (1);
}

int		parse_triangle(t_mini_rt *rt)
{
	t_element	*triangle;
	int			check;

	check = check_split(rt->split);
	if (!(triangle = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check < 5 || check > 6)
	{
		free(triangle);
		handle_error("triangle parsing error", rt);
	}
	triangle->id = 5;
	triangle->point = split_vec(rt->split[1], rt, 0);
	triangle->point2 = split_vec(rt->split[2], rt, 0);
	triangle->point3 = split_vec(rt->split[3], rt, 0);
	triangle->color = split_rgb(rt->split[4], rt);
	triangle->orient = vec_normalize(vec_cross(vec_sub(triangle->point2,
		triangle->point), vec_sub(triangle->point3, triangle->point)));
	triangle->ref = 0;
	check == 6 ? triangle->ref = ft_atof(rt->split[5]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(triangle));
	return (1);
}
