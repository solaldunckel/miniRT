/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:37:27 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/12 20:06:33 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	cylinder(t_mini_rt *rt, t_element *cylinder)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;
	t_vec	inter;

	t = 0;
	a = pow(rt->ray.dir.x, 2) + pow(rt->ray.dir.y, 2);
	b = 2 * (rt->ray.dir.x * (rt->ray.ori.x - cylinder->point.x)
		+ rt->ray.dir.y * (rt->ray.ori.y - cylinder->point.y));
	c = (pow(rt->ray.ori.x - cylinder->point.x, 2)
		+ pow(rt->ray.ori.y - cylinder->point.y, 2)
		- pow(cylinder->diameter / 2 / 1.5, 2));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
	{
		rt->t = -1;
		return ;
	}
	rt->t = intersect(a, b, det);
	inter = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->t));
	inter = vec_sub(cylinder->point, inter);
	inter.x < 0 ? inter.x *= -1 : 0;
	inter.y < 0 ? inter.y *= -1 : 0;
	inter.z < 0 ? inter.z *= -1 : 0;
	inter.x > cylinder->height / 2 || inter.y > cylinder->height / 2 || inter.z > cylinder->height / 2 ? rt->t = INT_MAX : 0;
}
