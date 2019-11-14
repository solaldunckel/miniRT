/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:16:49 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/14 16:55:18 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color		color_average(t_color color1, t_color color2)
{
	t_color		color;

	color.r = ((color1.r + color2.r) / 2);
	color.g = ((color1.g + color2.g) / 2);
	color.b = ((color1.b + color2.b) / 2);
	return (color);
}

void		apply_intensity(t_mini_rt *rt, double intensity)
{
	if (intensity > 1)
		return ;
	rt->color.r = rt->color.r * intensity;
	rt->color.g = rt->color.g * intensity;
	rt->color.b = rt->color.b * intensity;
	// rt->color.r > 255 ? rt->color.r = 255 : 0;
	// rt->color.g > 255 ? rt->color.r = 255 : 0;
	// rt->color.b > 255 ? rt->color.r = 255 : 0;
}

void		apply_lights(t_mini_rt *rt)
{
	t_list		*tmp;
	t_element	*light;
	double		dot;
	double		intensity;
	t_vec		P;
	t_vec		N;
	t_vec		L;

	intensity = rt->ambient.ratio;
	P = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->t));
	N = vec_normalize(vec_sub(P, rt->obj->point));
	tmp = rt->light_list;
	while (tmp)
	{
		light = tmp->content;
		L = vec_sub(light->point, P);
		dot = VEC_ADD(vec_dot(N, L));
		if (dot > 0)
			intensity += light->ratio * dot / (vec_len(N) * vec_len(L));
		tmp = tmp->next;
	}
	apply_intensity(rt, intensity);
}
