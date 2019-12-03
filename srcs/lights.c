/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:16:49 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/03 15:27:07 by haguerni         ###   ########.fr       */
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
	if (light->id == DIFFUSE)
	{
		light2.orient = dir;
		light2.point = light->point;
		plane(&rtt, &light2, ori, dir);
	}
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

t_vec			get_light_vec(t_element *light, t_vec p)
{
	t_vec	l;

	l.x = 0;
	l.y = 0;
	l.z = 0;
	if (light->id == DIFFUSE)
	{
		l = vec_normalize(vec_sub(light->point, p));
		light->orient = l;
	}
	else if (light->id == DIRECTIONAL)
		l = light->orient;
	return (l);
}

t_color			apply_intensity(float intensity, t_color color)
{
	if (intensity > 1)
		return (color);
	color.r = color.r * intensity;
	color.g = color.g * intensity;
	color.b = color.b * intensity;
	return (color);
}

t_color			rotate_color(t_mini_rt *rt, t_vec p, t_vec n, t_color color)
{
	t_list		*tmp;
	t_element	*light;
	float		dot;
	t_vec		l;

	tmp = rt->light_list;
	while (tmp)
	{
		light = element_cpy(tmp->content, rt);
		l = get_light_vec(light, p);
		dot = vec_dot(n, l);
		dot *= plane_side(rt, light, rt->obj->point, n);
		if (dot <= 0 || apply_shadows(rt, p, l, light))
		{
			tmp = tmp->next;
			free(light);
			continue;
		}
		color = color_add(color, color_average(rt->color,
			apply_intensity(light->ratio * dot, light->color)), 1);
		free(light);
		tmp = tmp->next;
	}
	return (color);
}

t_color			apply_lights(t_mini_rt *rt)
{
	t_vec		n;
	t_color		color;

	color = color_average(rt->color,
		apply_intensity(rt->ambient.ratio, rt->ambient.color));
	n = get_normal_vector(rt, rt->p);
	color = rotate_color(rt, rt->p, n, color);
	return (color);
}
