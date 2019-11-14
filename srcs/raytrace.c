/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/14 15:41:26 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	find_objs(t_mini_rt *rt, t_element *obj)
{
	if (obj->id == SPHERE)
		sphere(rt, obj);
	else if (obj->id == PLANE)
		plane(rt, obj);
	//ft_strequ(obj->id, SQUARE) ? square(rt, obj) : 0;
	//ft_strequ(obj->id, TRIANGLE) ? triangle(rt, obj) : 0;
	//ft_strequ(obj->id, CYLINDER) ? cylinder(rt, obj) : 0;
}

void	ray_inter(t_mini_rt *rt, int x, int y)
{
	t_list		*tmp;

	rt->obj = NULL;
	tmp = rt->objs_list;
	rt->t = INT_MAX;
	rt->k = INT_MAX;
	while (tmp)
	{
		find_objs(rt, tmp->content);
		if (rt->t > 0 && rt->t < rt->k)
		{
			rt->k = rt->t;
			rt->obj = tmp->content;
		}
		tmp = tmp->next;
	}
	if (rt->obj != NULL)
	{
		rt->color = rt->obj->color;
		apply_lights(rt);
		color_put(rt, x, y, R_TO_H(rt->color));
	}
}

t_vec	calc_ray(t_mini_rt *rt, int x, int y)
{
	t_vec	image_point;
	t_vec	dir;
	double	norm_x;
	double	norm_y;

	norm_x = ((x / (double)rt->res.x) - 0.5);
	norm_y = ((y / (double)rt->res.y) - 0.5);
	rt->res.x < rt->res.y ? norm_x *= rt->aspect : 0;
	rt->res.x > rt->res.y ? norm_y /= rt->aspect : 0;
	image_point = vec_add(vec_add(vec_mul(rt->cam_right, norm_x),
		vec_mul(rt->cam_up, norm_y)), vec_add(rt->ray.ori, rt->cam->orient));
	dir = vec_normalize(vec_sub(image_point, rt->ray.ori));
	return (dir);
}

void	raytracing(t_mini_rt *rt)
{
	double	x;
	double	y;

	y = -1;
	while (++y < rt->res.y)
	{
		x = -1;
		while (++x < rt->res.x)
		{
			rt->ray.dir = calc_ray(rt, x, y);
			ray_inter(rt, x, y);
		}
	}
}
