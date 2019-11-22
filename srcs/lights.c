/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:16:49 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 18:28:44 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static	int		plane_side(t_mini_rt *rt, t_element *light, t_vec ori,
t_vec dir)
{
	t_element	cam_plane;
	t_mini_rt	rtt;
	t_element	light2;

	if (rt->obj->id != PLANE && rt->obj->id != CIRCLE && rt->obj->id != SQUARE
	&& rt->obj->id != TRIANGLE)
		return (1);
	rtt.t = INT_MAX;
	light2.orient = dir;
	light2.point = light->point;
	plane(&rtt, &light2, ori, dir);
	rtt.k = rtt.t;
	cam_plane.point = rt->ray.ori;
	cam_plane.orient = dir;
	rtt.t = INT_MAX;
	plane(&rtt, &cam_plane, ori, dir);
	if (rtt.t == INT_MAX && rtt.k == INT_MAX)
		return (-1);
	if (rtt.t != INT_MAX && rtt.k != INT_MAX)
		return (1);
	return (0);
}

static	t_color	rotate_color(t_mini_rt *rt, t_vec p, t_vec n, t_color color)
{
	t_list		*tmp;
	t_element	*light;
	float		dot;
	t_vec		l;

	tmp = rt->light_list;
	while (tmp)
	{
		light = element_cpy(tmp->content);
		l = vec_normalize(vec_sub(light->point, p));
		dot = VEC_ADD(vec_dot(n, l));
		dot *= plane_side(rt, light, rt->obj->point, n);
		light->orient = l;
		if (apply_shadows(rt, p, l, light))
		{
			tmp = tmp->next;
			free(light);
			continue;
		}
		dot > 0 ? rt->intensity += light->ratio * dot / vec_len(l) : 0;
		dot < 0 ? color = color_average(color, light->color) : color;
		free(light);
		tmp = tmp->next;
	}
	return (color);
}

void			apply_intensity(t_mini_rt *rt, float intensity, t_color *color)
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
	t_vec		p;
	t_vec		n;
	t_color		color;

	rt->intensity = rt->ambient.ratio;
	color = rt->ambient.color;
	p = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->k));
	if (rt->obj->id == PLANE || rt->obj->id == CIRCLE || rt->obj->id == SQUARE)
		n = rt->obj->orient;
	else if (rt->obj->id == CONE)
		n = vec_normalize(vec_sub(p, vec_add(rt->obj->point,
		vec_mul(rt->obj->orient, vec_len(vec_sub(p, rt->obj->point)) * -1))));
	else
		n = vec_normalize(vec_sub(p, rt->obj->point));
	color = rotate_color(rt, p, n, color);
	color = color_average(color, rt->obj->color);
	apply_intensity(rt, rt->intensity, &color);
	return (color);
}
