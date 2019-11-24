/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:36:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/23 18:57:54 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	plane(t_mini_rt *rt, t_element *plane, t_vec ori, t_vec dir)
{
	t_solve	s;
	float	t;

	s.a = vec_dot(vec_sub(ori, plane->point), plane->orient);
	s.b = vec_dot(dir, plane->orient);
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return ;
	t = -s.a / s.b;
	if (t < 0 || rt->t < t)
		return ;
	rt->t = t;
}
