/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:57:29 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/01 22:54:06 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	triangle(t_mini_rt *rt, t_element *triangle, t_vec ori, t_vec dir)
{
	t_solve	s;
	t_vec	v1;
	t_vec	v2;
	t_vec	tvec;
	t_vec	pvec;

	v1 = vec_sub(triangle->point2, triangle->point);
	v2 = vec_sub(triangle->point3, triangle->point);
	pvec = vec_cross(dir, v2);
	s.det = vec_dot(v1, pvec);
	if (fabs(s.det) < 0.00001)
		return ;
	s.c = 1 / s.det;
	tvec = vec_sub(ori, triangle->point);
	s.a = vec_dot(tvec, pvec) * s.c;
	if (s.a < 0 || s.a > 1)
		return ;
	tvec = vec_cross(tvec, v1);
	s.b = vec_dot(dir, tvec) * s.c;
	if (s.b < 0 || s.a + s.b > 1)
		return ;
	rt->t = vec_dot(v2, tvec) * s.c;
}
