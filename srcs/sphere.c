/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:10:22 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 14:02:34 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	sphere(t_mini_rt *rt, t_element *sphere)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;

	t = 0;
	a = VEC_ADD(vec_dot(rt->ray.dir, rt->ray.dir));
	b = 2 * VEC_ADD(vec_dot(rt->ray.dir, vec_sub(rt->cam->pov, sphere->point)));
	c = VEC_ADD(vec_dot(vec_sub(rt->cam->pov, sphere->point),
		vec_sub(rt->cam->pov, sphere->point))) - pow(sphere->diameter / 2, 2);
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
	{
		rt->t = -1;
		return ;
	}
	rt->t = intersect(a, b, det);
}
