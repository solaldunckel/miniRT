/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:36:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/12 12:40:33 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	plane(t_mini_rt *rt, t_element *plane)
{
	double	a;
	double	b;

	a = VEC_ADD(vec_dot(vec_sub(rt->cam->pov, plane->point), plane->orient));
	b = VEC_ADD(vec_dot(rt->ray.dir, plane->orient));
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
	{
		rt->t = -1;
		return ;
	}
	rt->t = -a / b;
	if (rt->t < 0)
		rt->t = -1;
}
