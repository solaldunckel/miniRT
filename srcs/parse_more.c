/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:40:08 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/30 21:52:24 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_antialiasing(t_mini_rt *rt)
{
	if (check_split(rt->split) != 2)
		handle_error("invalid anti aliasing", rt);
	rt->anti_aliasing = ft_atoi(rt->split[1]);
	if (rt->anti_aliasing < 1)
		handle_error("anti aliasing too small", rt);
	return (1);
}

int		parse_cone(t_mini_rt *rt)
{
	t_element	*cone;
	int			check;

	check = check_split(rt->split);
	if (!(cone = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check < 6 || check > 7)
	{
		free(cone);
		handle_error("cone parsing error", rt);
	}
	cone->id = 7;
	cone->point = split_vec(rt->split[1], rt, 0);
	cone->orient = split_vec(rt->split[2], rt, 1);
	cone->diameter = ft_atof(rt->split[3]);
	cone->height = ft_atof(rt->split[4]);
	cone->color = split_rgb(rt->split[5], rt);
	cone->ref = 0;
	check == 7 ? cone->ref = ft_atof(rt->split[6]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(cone));
	if (cone->height < 0 || cone->diameter < 0)
		handle_error("cone parsing error", rt);
	create_circle(rt, cone, cone->height * -1);
	return (1);
}

int		parse_cube(t_mini_rt *rt)
{
	t_element	cube;

	if (check_split(rt->split) != 4)
		handle_error("cube parsing error", rt);
	cube.point = split_vec(rt->split[1], rt, 0);
	cube.height = ft_atof(rt->split[2]);
	cube.color = split_rgb(rt->split[3], rt);
	create_square(rt, &cube, cube.point, (t_vec){0, 0, 1});
	create_square(rt, &cube, (t_vec){cube.point.x, cube.point.y,
		cube.point.z + cube.height}, (t_vec){0, 0, 1});
	create_square(rt, &cube, (t_vec){cube.point.x + cube.height / 2,
		cube.point.y, cube.point.z + cube.height / 2}, (t_vec){1, 0, 0});
	create_square(rt, &cube, (t_vec){cube.point.x - cube.height / 2,
		cube.point.y, cube.point.z + cube.height / 2}, (t_vec){1, 0, 0});
	create_square(rt, &cube, (t_vec){cube.point.x, cube.point.y
		+ cube.height / 2, cube.point.z + cube.height / 2},
		(t_vec){0, 1, 0});
	create_square(rt, &cube, (t_vec){cube.point.x, cube.point.y
		- cube.height / 2, cube.point.z + cube.height / 2},
		(t_vec){0, 1, 0});
	return (1);
}

int		parse_dir_light(t_mini_rt *rt)
{
	t_element		*light;

	if (!(light = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 4)
	{
		free(light);
		handle_error("dir light parsing error", rt);
	}
	light->id = 11;
	light->orient = split_vec(rt->split[1], rt, 1);
	light->ratio = ft_atof(rt->split[2]);
	light->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->light_list, ft_lstnew(light));
	if (light->ratio > 1 || light->ratio < 0)
		handle_error("dir light parsing error", rt);
	return (1);
}

int		parse_sky(t_mini_rt *rt)
{
	t_texture	*sky;
	int			i;

	if (!(sky = ft_calloc(1, sizeof(t_texture) * 7)))
		handle_error("fail to malloc", rt);
	i = 0;
	while (rt->split[++i])
	{
		if (!ft_str_end(rt->split[i], ".xpm"))
		{
			free(sky);
			handle_error("sky parsing error", rt);
		}
		sky[i - 1] = create_sky(rt, rt->split[i]);
	}
	rt->sky = sky;
	return (1);
}
