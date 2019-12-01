/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:20:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/01 21:48:47 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static	void	inter_cone(t_mini_rt *rt, t_element *cone, t_solve s,
t_mini_rt rtt)
{
	t_element	plan;
	t_vec		inter;
	float		t;

	t = INT_MAX;
	if (s.t1 >= 0 && rt->t > s.t1)
		t = s.t1;
	else if (s.t2 >= 0 && rt->t > s.t2)
		t = s.t2;
	if (t == INT_MAX)
		return ;
	inter = vec_add(rtt.ray.ori, vec_mul(rtt.ray.dir, t));
	plan.orient = cone->orient;
	plan.point = cone->point;
	rtt.t = INT_MAX;
	plane(&rtt, &plan, inter, vec_normalize(cone->orient));
	rtt.t <= cone->height ? rt->t = t : 0;
}

void			cone(t_mini_rt *rt, t_element *cone, t_vec ori, t_vec dir)
{
	t_solve		s;
	t_mini_rt	rtt;
	t_vec		w;
	t_vec		theta;
	float		m;

	rtt.ray.ori = ori;
	rtt.ray.dir = dir;
	theta = vec_normalize(cone->orient);
	m = pow(cone->diameter / 2, 2) / pow(cone->height, 2);
	w = vec_sub(rtt.ray.ori, cone->point);
	s.d1 = vec_dot(rtt.ray.dir, theta);
	s.d2 = vec_dot(w, theta);
	s.a = pow(s.d1, 2);
	s.a = vec_dot(rtt.ray.dir, rtt.ray.dir) - m * s.a - s.a;
	s.b = 2 * (vec_dot(rtt.ray.dir, w) - m * s.d1 * s.d2 - s.d1 * s.d2);
	s.c = vec_dot(w, w) - m * pow(s.d2, 2) - pow(s.d2, 2);
	s.det = pow(s.b, 2) - (4 * s.a * s.c);
	if (s.det < 0)
		return ;
	s.det = sqrt(s.det);
	s.t1 = (-s.b - s.det) / (2 * s.a);
	s.t2 = (-s.b + s.det) / (2 * s.a);
	inter_cone(rt, cone, s, rtt);
}
