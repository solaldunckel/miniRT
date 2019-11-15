/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:36:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 15:41:52 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	plane(t_mini_rt *rt, t_element *plane, t_vec ori, t_vec dir)
{
	double	a;
	double	b;

	a = VEC_ADD(vec_dot(vec_sub(ori, plane->point), plane->orient));
	b = VEC_ADD(vec_dot(dir, plane->orient));
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
	{
		rt->t = INT_MAX;
		return ;
	}
	rt->t = -a / b;
	if (rt->t < 0)
		rt->t = INT_MAX;
}
