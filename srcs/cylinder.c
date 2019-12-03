/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:37:27 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/03 10:47:53 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static	void	inter(t_mini_rt *rt, t_element *cylinder, t_solve s,
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
	plan.orient = cylinder->orient;
	plan.point = cylinder->point;
	rtt.t = INT_MAX;
	plane(&rtt, &plan, inter, cylinder->orient);
	rtt.t <= cylinder->height / 2 ? rt->t = t : 0;
	plane(&rtt, &plan, inter, vec_mul(cylinder->orient, -1));
	rtt.t <= cylinder->height / 2 ? rt->t = t : 0;
}

void			cylinder(t_mini_rt *rt, t_element *cylinder, t_vec ori,
					t_vec dir)
{
	t_solve		s;
	t_mini_rt	rtt;

	rtt.ray.ori = ori;
	rtt.ray.dir = dir;
	s.sub = vec_sub(rtt.ray.ori, cylinder->point);
	s.cross = vec_cross(rtt.ray.dir, cylinder->orient);
	s.a = vec_dot(s.cross, s.cross);
	s.cross = vec_cross(s.sub, cylinder->orient);
	s.b = 2 * s.a;
	s.c = s.a - (pow(cylinder->diameter / 2, 2)
		* vec_dot(cylinder->orient, cylinder->orient));
	s.det = pow(s.b, 2) - (4 * s.a * s.c);
	if (s.det < 0)
		return ;
	s.a = 2 * s.a;
	s.det = sqrt(s.det);
	s.t1 = (-s.b - s.det) / s.a;
	s.t2 = (-s.b + s.det) / s.a;
	inter(rt, cylinder, s, rtt);
}
