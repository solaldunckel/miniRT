/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:40:08 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 17:51:01 by haguerni         ###   ########.fr       */
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

	if (!(cone = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 6)
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
	ft_lstadd_back(&rt->objs_list, ft_lstnew(cone));
	if (cone->height < 0 || cone->diameter < 0)
		handle_error("cone parsing error", rt);
	create_circle(rt, cone, cone->height * -1);
	return (1);
}
