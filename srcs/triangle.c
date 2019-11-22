/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:57:29 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/21 17:44:01 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void 	print_vec(t_vec v)
{
	printf("%f,%f,%f\n", v.x, v.y, v.z);
}

void	triangle(t_mini_rt *rt, t_element *triangle, t_vec ori, t_vec dir)
{
	t_solve	s;
	t_vec	v1;
	t_vec	v2;
	t_vec	tvec;
	t_vec	qvec;
	t_vec	pvec;
	float	inv_det;

	v1 = vec_sub(triangle->point2, triangle->point);
	v2 = vec_sub(triangle->point3, triangle->point);
	pvec = vec_cross(dir, v2);
	s.det = VEC_ADD(vec_cross(v1, pvec));
	if (fabs(s.det) < 0.000001)
		return;
	inv_det = 1 / s.det;
	tvec = vec_sub(ori, triangle->point);
	s.a = VEC_ADD(vec_mul(vec_dot(tvec, pvec), inv_det));
	if (s.a < 0 || s.a > 1)
		return ;
	qvec = vec_cross(tvec, v1);
	s.b = VEC_ADD(vec_mul(vec_dot(dir, qvec), inv_det));
	if (s.b < 0 || s.a + s.b > 1)
		return;
	s.b = VEC_ADD(vec_dot(v2, qvec)) * inv_det;
	s.b < rt->t ? rt->t = s.b : 0;
}
