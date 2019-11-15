/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:37:27 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 17:05:31 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*static	void	circle_check(t_mini_rt *rt, t_element *cylinder)
{
	t_element	circle1;
	t_element	circle2;

	circle1.diameter = cylinder->diameter;
	circle2.diameter = cylinder->diameter;
}*/

static	void	inter(t_mini_rt *rt, t_element *cylinder, double tsave2,
t_solve s)
{
	double 		tsave;
	t_element	plan;
	t_vec		inter;

	s.t1 = (-s.b - sqrt(s.det)) / (2 * s.a);
	s.t2 = (-s.b + sqrt(s.det)) / (2 * s.a);
	if (s.t1 >= 0 && rt->t > s.t1)
		rt->t = s.t1;
	else if (s.t2 >= 0 && rt->t > s.t2)
		rt->t = s.t2;
	tsave = rt->t;
	inter = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->t));
	plan.orient = cylinder->orient;
	plan.point = cylinder->point;
	plane(rt, &plan, inter, cylinder->orient);
	rt->t > cylinder->height / 2 || rt->t > cylinder->height / 2 ||
	rt->t > cylinder->height / 2 ? rt->t = tsave2 : 0;
	rt->t <= cylinder->height / 2 || rt->t <= cylinder->height / 2 ||
	rt->t <= cylinder->height / 2 ? rt->t = tsave : 0;
	plane(rt, &plan, inter, vec_mul(cylinder->orient, -1));
	rt->t > cylinder->height / 2 || rt->t > cylinder->height / 2 ||
	rt->t > cylinder->height / 2 ? rt->t = tsave2 : 0;
	rt->t <= cylinder->height / 2 || rt->t <= cylinder->height / 2 ||
	rt->t <= cylinder->height / 2 ? rt->t = tsave : 0;
}

void			cylinder(t_mini_rt *rt, t_element *cylinder)
{
	t_solve		s;
	double		tsave2;


	s.a = VEC_ADD(vec_dot(vec_cross(rt->ray.dir, cylinder->orient),
	vec_cross(rt->ray.dir, cylinder->orient)));
	s.b = 2 * VEC_ADD(vec_dot(vec_cross(rt->ray.dir, cylinder->orient),
	vec_cross(vec_sub(rt->ray.ori, cylinder->point), cylinder->orient)));
	s.c = VEC_ADD(vec_dot(vec_cross(vec_sub(rt->ray.ori, cylinder->point),
	cylinder->orient), vec_cross(vec_sub(rt->ray.ori, cylinder->point),
	cylinder->orient))) - (pow(cylinder->diameter / 2, 2)
	* VEC_ADD(vec_dot(cylinder->orient, cylinder->orient)));
	s.det = pow(s.b, 2) - (4 * s.a * s.c);
	tsave2 = rt->t;
	if (s.det < 0)
		return ;
	inter(rt, cylinder, tsave2, s);
	//circle_check(rt, cylinder);
}
