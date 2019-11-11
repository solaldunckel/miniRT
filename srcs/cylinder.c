/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:37:27 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 11:38:04 by sdunckel         ###   ########.fr       */
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

	t = 0;
	a = pow(rt->ray.dir.x, 2) + pow(rt->ray.dir.y, 2);
	b = 2 * (rt->ray.dir.x * (rt->cam->pov.x - cylinder->point.x)
		+ rt->ray.dir.y * (rt->cam->pov.y - cylinder->point.y));
	c = (pow(rt->cam->pov.x - cylinder->point.x, 2)
		+ pow(rt->cam->pov.y - cylinder->point.y, 2)
		- pow(cylinder->diameter / 1.5, 2));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
	{
		rt->t = -1;
		return ;
	}
	rt->t = intersect(a, b, det);
}
