/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 16:13:38 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_sphere(t_mini_rt *rt, t_element *sphere)
{
	(void)sphere;
	(void)rt;
	printf("%s\n", sphere->id);
}

void	ft_square(t_mini_rt *rt, t_element *square)
{
	(void)square;
	(void)rt;
	printf("%s\n", square->id);
}

void	ft_plane(t_mini_rt *rt, t_element *plane)
{
	(void)plane;
	(void)rt;
	printf("%s\n", plane->id);
}

void	ft_triangle(t_mini_rt *rt, t_element *triangle)
{
	(void)triangle;
	(void)rt;
	printf("%s\n", triangle->id);
}

void	ft_cylinder(t_mini_rt *rt, t_element *cylinder)
{
	(void)cylinder;
	(void)rt;
	printf("%s\n", cylinder->id);
}

void	ft_ray(t_mini_rt *rt)
{
	t_list		*temp;
	t_element 	*elem;

	temp = rt->list;
	while (temp)
	{
		elem = temp->content;
		ft_strequ(elem->id, "sphere") ? ft_sphere(rt, elem) : 0;
		//ft_strequ(elem->id, "square") ? ft_square(rt, elem) : 0;
		//ft_strequ(elem->id, "plane") ? ft_plane(rt, elem) : 0;
		//ft_strequ(elem->id, "triangle") ? ft_triangle(rt, elem) : 0;
		//ft_strequ(elem->id, "cylinder") ? ft_cylinder(rt, elem) : 0;
		temp = temp->next;
	}
}

int		raytracing(t_mini_rt *rt)
{
	rt->y = 0;
	while (rt->y < rt->res.y)
	{
		rt->x = 0;
		while (rt->x < rt->res.x)
		{
			ft_ray(rt);
			color_put(rt);
			rt->x++;
		}
		rt->y++;
	}
	return (0);
}
