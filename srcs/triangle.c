/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:57:29 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 21:59:19 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	triangle(t_mini_rt *rt, t_element *triangle, t_vec ori, t_vec dir)
{
	t_solve	s;
	t_vec	v0v1;
	t_vec	v0v2;
	t_vec	tvec;
	t_vec	qvec;
	t_vec	pvec;
	double	inv_det;

	v0v1 = vec_sub(triangle->point2, triangle->point);
	v0v2 = vec_sub(triangle->point3, triangle->point);
	pvec = vec_cross(dir, v0v2);
	s.det = VEC_ADD(vec_cross(v0v1, pvec));
	if (s.det < 0.00001)
		return ;
	if (fabs(s.det) < 0.00001)
		return ;
	inv_det = 1 / s.det;
	tvec = vec_sub(ori, triangle->point);
	s.a = VEC_ADD(vec_mul(vec_dot(tvec, pvec), inv_det));
	if (s.a < 0 || s.a > 1)
		return ;
	qvec = vec_cross(tvec, v0v1);
	s.b = VEC_ADD(vec_mul(vec_dot(dir, qvec), inv_det));
	if (s.b < 0 || s.a + s.b > 1)
		return;
	rt->t = VEC_ADD(vec_mul(vec_dot(v0v2, qvec), inv_det));
}
