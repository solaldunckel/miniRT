/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:40:08 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/26 17:04:30 by haguerni         ###   ########.fr       */
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
	t_element		*cone;
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
	light->orient = split_vec(rt->split[1], rt, 0);
	light->ratio = ft_atof(rt->split[2]);
	light->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->light_list, ft_lstnew(light));
	if (light->ratio > 1 || light->ratio < 0)
		handle_error("dir light parsing error", rt);
	return (1);
}
