/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:51:52 by haguerni          #+#    #+#             */
/*   Updated: 2019/11/30 21:09:22 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec		get_cylinder_normal(t_element *cylinder, t_vec p)
{
	t_element	plan;
	t_mini_rt	rtt;

	plan.orient = cylinder->orient;
	plan.point = cylinder->point;
	rtt.t = INT_MAX;
	plane(&rtt, &plan, p, cylinder->orient);
	if (rtt.t != INT_MAX)
	{
		return (vec_normalize(vec_sub(p, vec_add(cylinder->point,
			vec_mul(cylinder->orient, rtt.t * -1)))));
	}
	plane(&rtt, &plan, p, vec_mul(cylinder->orient, -1));
	return (vec_normalize(vec_sub(p, vec_add(cylinder->point,
		vec_mul(cylinder->orient, rtt.t)))));
}

t_vec		get_normal_vector(t_mini_rt *rt, t_vec p)
{
	t_vec	norm_vec;

	if (rt->obj->id == PLANE || rt->obj->id == CIRCLE || rt->obj->id == SQUARE
		|| rt->obj->id == TRIANGLE)
		norm_vec = vec_normalize(rt->obj->orient);
	else if (rt->obj->id == CONE)
		norm_vec = vec_normalize(vec_sub(p, vec_add(rt->obj->point,
			vec_mul(rt->obj->orient, vec_len(vec_sub(p, rt->obj->point))
			* -1))));
	else if (rt->obj->id == CYLINDER)
		norm_vec = get_cylinder_normal(rt->obj, p);
	else
		norm_vec = vec_normalize(vec_sub(p, rt->obj->point));
	return (norm_vec);
}

t_color		color_average3(t_color color1, t_color color2, float intens)
{
	t_color		color;

	if (intens == 0)
		return (color1);
	color.r = (color1.r + color2.r * intens) / 2;
	color.g = (color1.g + color2.g * intens) / 2;
	color.b = (color1.b + color2.b * intens) / 2;
	return (color);
}

void		reflect(t_mini_rt *rt)
{
	t_mini_rt	rtt;

	rt->nbref++;
	if (rt->nbref > MAX_REF)
		return ;
	ft_memcpy(&rtt, rt, sizeof(t_mini_rt));
	rtt.ray.ori = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->k));
	rtt.ray.dir = get_normal_vector(rt, rtt.ray.ori);
	rt->obj->ref < 0 ? rtt.ray.dir = vec_mul(rtt.ray.dir, -1) : rtt.ray.dir;
	rt->obj->ref > 0 ? rtt.ray.dir = vec_normalize(vec_sub(rt->ray.dir,
		vec_mul(vec_mul(rtt.ray.dir, vec_dot(rtt.ray.dir, rt->ray.dir)), 2)))
		: rtt.ray.dir;
	rt->obj->ref < 0 ? rtt.ray.dir = vec_normalize(vec_sub(rt->ray.dir,
		vec_mul(vec_mul(rtt.ray.dir, vec_dot(vec_mul(rtt.ray.dir, rt->obj->ref),
		rt->ray.dir)), 2))) : rtt.ray.dir;
	rtt.ray.ori = vec_add(rtt.ray.ori, vec_mul(rtt.ray.dir, 0.1));
	rtt.color = ray_intersect(&rtt);
	rt->obj->ref > 0 ? rt->color = color_average3(rt->color, rtt.color,
		rt->obj->ref) : rt->color;
	rt->obj->ref < 0 ? rt->color = color_average3(rt->color, rtt.color, 1)
		: rt->color;
}
