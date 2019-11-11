/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:10:22 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 01:47:08 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		intersect(double a, double b, double det)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(det)) / (2 * a);
	t2 = (-b + sqrt(det)) / (2 * a);
	return (t1 < t2 ? t1 : t2);
}

void	sphere(t_mini_rt *rt, t_element *sphere)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;

	t = 0;
	a = pow(rt->ray.dir.x, 2) + pow(rt->ray.dir.y, 2) + pow(rt->ray.dir.z, 2);
	b = 2 * (rt->ray.dir.x * (rt->cam->pov.x - sphere->point.x)
		+ rt->ray.dir.y * (rt->cam->pov.y - sphere->point.y) + rt->ray.dir.z
		* (rt->cam->pov.z - sphere->point.z));
	c = (pow(rt->cam->pov.x - sphere->point.x, 2)
		+ pow(rt->cam->pov.y - sphere->point.y, 2)
		+ pow(rt->cam->pov.z - sphere->point.z, 2))
		- pow(sphere->diameter / 2, 2);
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
	{
		rt->t = -1;
		return ;
	}
	rt->t = intersect(a, b, det);
}
