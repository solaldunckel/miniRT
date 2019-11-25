/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:51:52 by haguerni          #+#    #+#             */
/*   Updated: 2019/11/25 17:19:02 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	reflect(t_mini_rt *rt)
{
	t_mini_rt	rtt;

	rt->nbref++;
	if (rt->nbref > MAX_REF)
		return ;
	ft_memcpy(&rtt, rt, sizeof(t_mini_rt));
	rtt.ray.ori = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->k));
	rtt.ray.dir = vec_normalize(vec_sub(rtt.ray.ori, rt->obj->point));
	rtt.ray.dir = vec_normalize(vec_sub(rt->ray.dir,
	vec_mul(vec_mul(rtt.ray.dir, vec_dot(rtt.ray.dir, rt->ray.dir)), 2)));
	rtt.ray.ori = vec_add(rtt.ray.ori, vec_mul(rtt.ray.dir, 0.1));
	rtt.color = ray_intersect(&rtt);
	apply_intensity(rt->obj->ref, &rtt.color);
	rt->color = color_average(rt->color, rtt.color);
	//apply_intensity(rt->obj->ref, &rtt.color);
}
