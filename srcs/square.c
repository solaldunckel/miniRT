/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:57:20 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 00:24:53 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	square(t_mini_rt *rt, t_element *square, t_vec ori, t_vec dir)
{
	t_solve	s;
	t_vec	d;

	s.a = VEC_ADD(vec_dot(vec_sub(ori, square->point), square->orient));
	s.b = VEC_ADD(vec_dot(dir, square->orient));
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return ;
	s.t1 = -s.a / s.b;
	d = vec_sub(vec_add(vec_mul(dir, s.t1), ori), square->point);
	s.t2 = square->height / 2;
	if (fabs(d.x) > s.t2 || fabs(d.y) > s.t2 || fabs(d.z) > s.t2)
		return ;
	if (s.t1 > 0)
		rt->t = s.t1;
}
