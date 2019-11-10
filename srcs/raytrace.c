/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/10 17:10:47 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ray(t_mini_rt *rt)
{
	t_list		*temp;
	t_element 	*elem;

	temp = rt->list;
	while (temp)
	{
		elem = temp->content;
		ft_strequ(elem->id, SPHERE) ? sphere(rt, elem) : 0;
		//ft_strequ(elem->id, SQUARE) ? square(rt, elem) : 0;
		//ft_strequ(elem->id, PLANE) ? plane(rt, elem) : 0;
		//ft_strequ(elem->id, TRIANGLE) ? triangle(rt, elem) : 0;
		//ft_strequ(elem->id, CYLINDER) ? cylinder(rt, elem) : 0;
		temp = temp->next;
	}
}

int		raytracing(t_mini_rt *rt)
{
	int		x;
	int		y;
	float 	angle;

	y = 0;
	rt->cam->fov = 70;
	rt->t = 0;
	angle = tan(M_PI * 0.5 * rt->cam->fov / 180);
	rt->ray.ori = rt->cam->point;
	while (y < rt->res.y)
	{
		x = 0;
		while (x < rt->res.x)
		{
			rt->ray.dir.x = 2 * ((x + 0.5) / rt->res.x) - 1 * angle;
			rt->ray.dir.y = 1 - 2 * ((y + 0.5) / rt->res.y) * angle;
			rt->ray.dir.z = -1;
			rt->col = 0x000000;
			ray(rt);
			color_put(rt, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
