/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 12:42:49 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	find_objs(t_mini_rt *rt, t_element *obj)
{
	ft_strequ(obj->id, SPHERE) ? sphere(rt, obj) : 0;
	//ft_strequ(obj->id, SQUARE) ? square(rt, obj) : 0;
	ft_strequ(obj->id, PLANE) ? plane(rt, obj) : 0;
	//ft_strequ(obj->id, TRIANGLE) ? triangle(rt, obj) : 0;
	//ft_strequ(obj->id, CYLINDER) ? cylinder(rt, obj) : 0;
}

void	ray_inter(t_mini_rt *rt, int x, int y)
{
	t_list		*tmp;

	rt->obj = NULL;
	rt->color = 0x000000;
	tmp = rt->elem_list;
	rt->k = 0;
	while (tmp)
	{
		find_objs(rt, tmp->content);
		if (rt->t >= 0 && rt->k <= rt->t)
		{
			rt->k = rt->t;
			rt->obj = tmp->content;
		}
		tmp = tmp->next;
	}
	if (rt->obj)
	{
		// calcul de couleur sur le dernier objet ???
		rt->color = convert_rgb(rt->obj->color);
		color_put(rt, x, y);
	}
}

int		raytracing(t_mini_rt *rt)
{
	int		x;
	int		y;
	double 	angle;

	rt->cam->fov = 70;
	rt->k = 0;
	rt->t = 0;
	angle = tan(M_PI * 0.5 * rt->cam->fov / 180);
	y = -1;
	while (++y < rt->res.y)
	{
		x = -1;
		while (++x < rt->res.x)
		{
			rt->ray.dir.x = (2 * (x + 0.5) / rt->res.x) - 1 * angle;
			rt->ray.dir.y = (1 - 2 * (y + 0.5) / rt->res.y) * angle;
			rt->ray.dir.z = -1;
			ray_inter(rt, x, y);
		}
	}
	return (0);
}
