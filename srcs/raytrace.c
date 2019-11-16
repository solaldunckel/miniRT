/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 13:52:14 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	find_objs(t_mini_rt *rt, t_element *obj)
{
	if (obj->id == SPHERE)
		sphere(rt, obj, rt->ray.ori, rt->ray.dir);
	else if (obj->id == PLANE)
		plane(rt, obj, rt->ray.ori, rt->ray.dir);
	else if (obj->id == CYLINDER)
		cylinder(rt, obj, rt->ray.ori, rt->ray.dir);
	else if (obj->id == CIRCLE)
		circle(rt, obj, rt->ray.ori, rt->ray.dir);
	else if (obj->id == TRIANGLE)
		triangle(rt, obj, rt->ray.ori, rt->ray.dir);
	else if (obj->id == SQUARE)
	 	square(rt, obj, rt->ray.ori, rt->ray.dir);
}

t_color	ray_intersect(t_mini_rt *rt)
{
	t_list		*tmp;
	t_color		color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	rt->obj = NULL;
	rt->t = INT_MAX;
	rt->k = INT_MAX;
	tmp = rt->objs_list;
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
		color = apply_lights(rt);
	return (color);
}

t_vec	calc_ray(t_mini_rt *rt, double x, double y)
{
	t_vec	image_point;
	t_vec	dir;
	double	norm_x;
	double	norm_y;

	norm_x = ((x / (double)rt->res.x) - 0.5);
	norm_y = ((y / (double)rt->res.y) - 0.5);
	rt->res.x < rt->res.y ? norm_x *= rt->aspect : 0;
	rt->res.x > rt->res.y ? norm_y /= rt->aspect : 0;
	image_point = vec_add(vec_add(vec_mul(rt->cam->right, norm_x),
		vec_mul(rt->cam->up, norm_y)), vec_add(rt->ray.ori, rt->cam->orient));
	dir = vec_normalize(vec_sub(image_point, rt->ray.ori));
	return (dir);
}

void	raytracing(t_mini_rt *rt)
{
	double	i;
	double	j;

	j = -1;
	while (++j < rt->res.y)
	{
		i = -1;
		while (++i < rt->res.x)
		{
			rt->ray.dir = calc_ray(rt, i , j);
			rt->color = ray_intersect(rt);
			if (rt->obj)
				color_put(rt, i, j, R_TO_H(rt->color));
		}
	}
}
