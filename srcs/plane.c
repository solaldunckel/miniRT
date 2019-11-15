/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:36:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 17:32:03 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	plane(t_mini_rt *rt, t_element *plane, t_vec ori, t_vec dir)
{
	double	a;
	double	b;
	double	t;

	a = VEC_ADD(vec_dot(vec_sub(ori, plane->point), plane->orient));
	b = VEC_ADD(vec_dot(dir, plane->orient));
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return ;
	t = -a / b;
	if (t < 0)
		return;
	rt->t = t;
}
