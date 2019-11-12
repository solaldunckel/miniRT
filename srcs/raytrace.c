/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/12 12:40:59 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	find_objs(t_mini_rt *rt, t_element *obj)
{
	ft_strequ(obj->id, SPHERE) ? sphere(rt, obj) : 0;
	//ft_strequ(obj->id, SQUARE) ? square(rt, obj) : 0;
	ft_strequ(obj->id, PLANE) ? plane(rt, obj) : 0;
	//ft_strequ(obj->id, TRIANGLE) ? triangle(rt, obj) : 0;
//	ft_strequ(obj->id, CYLINDER) ? cylinder(rt, obj) : 0;
}

void	ray_inter(t_mini_rt *rt, int x, int y)
{
	t_list		*tmp;

	rt->obj = NULL;
	rt->color = 0x000000;
	tmp = rt->elem_list;
	rt->t = 0;
	rt->k = 0;
	while (tmp)
	{
		find_objs(rt, tmp->content);
		if (rt->t > 0 && rt->k < rt->t)
		{
			rt->k = rt->t;
			rt->obj = tmp->content;
		}
		tmp = tmp->next;
	}
	if (rt->obj)
	{
		// calcul de couleur sur le dernier objet ???
		rt->color = R_TO_H(rt->obj->color);
		color_put(rt, x, y);
	}
}

int		raytracing(t_mini_rt *rt)
{
	int		x;
	int		y;
	double	angle;
	double	ratio;

	rt->cam->fov = 70;
	rt->k = 0;
	rt->t = 0;
	angle = tan(rt->cam->fov / 2 * M_PI / 180);
	ratio = (double)rt->res.x / (double)rt->res.y;
	y = -1;
	rt->ray.ori = VEC_CREATE(rt->cam->pov.x, rt->cam->pov.y, rt->cam->pov.z);
	while (++y < rt->res.y)
	{
		x = -1;
		while (++x < rt->res.x)
		{
			rt->ray.dir = VEC_CREATE(
				(2 * (x + 0.5) / (double)rt->res.x - 1) * angle * ratio,
				-(2 * (y + 0.5) / (double)rt->res.y - 1) * angle,
				-1);
			rotate_vector(&rt->ray.dir, &rt->cam->orient);
			vec_normalize(&rt->ray.dir);
			ray_inter(rt, x, y);
		}
	}
	return (0);
}
