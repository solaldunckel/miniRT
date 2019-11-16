/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:16:49 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 21:33:20 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void			apply_intensity(t_mini_rt *rt, double intensity, t_color *color)
{
	(void)rt;
	if (intensity > 1)
		return ;
	color->r = color->r * intensity;
	color->g = color->g * intensity;
	color->b = color->b * intensity;
}

t_color			apply_lights(t_mini_rt *rt)
{
	t_list		*tmp;
	t_element	*light;
	double		dot;
	t_vec		p;
	t_vec		n;
	t_vec		l;
	t_color		color;

	rt->intensity = rt->ambient.ratio;
	color = rt->ambient.color;
	p = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->k));
	if (rt->obj->id == PLANE || rt->obj->id == CIRCLE || rt->obj->id == TRIANGLE
		|| rt->obj->id == SQUARE)
		n = rt->obj->orient;
	else
		n = vec_normalize(vec_sub(p, rt->obj->point));
	tmp = rt->light_list;
	while (tmp)
	{
		light = tmp->content;
		l = vec_normalize(vec_sub(light->point, p));
		dot = VEC_ADD(vec_dot(n, l));
		// if (!apply_shadows(rt, p, l))
		// {
		// 	tmp = tmp->next;
		// 	continue ;
		// }
		if (dot > 0)
		{
			rt->intensity += light->ratio * dot / (vec_len(n) * vec_len(l));
			color = color_average(color, light->color);
		}
		tmp = tmp->next;
	}
	color = color_average(color, rt->obj->color);
	apply_intensity(rt, rt->intensity, &color);
	return (color);
}
