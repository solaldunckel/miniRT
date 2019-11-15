/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:10:22 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 15:51:32 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	sphere(t_mini_rt *rt, t_element *sphere, t_vec ori, t_vec dir)
{
	t_solve	s;

	s.a = VEC_ADD(vec_dot(dir, dir));
	s.b = 2 * VEC_ADD(vec_dot(dir, vec_sub(ori, sphere->point)));
	s.c = VEC_ADD(vec_dot(vec_sub(ori, sphere->point),
		vec_sub(ori, sphere->point))) - pow(sphere->diameter / 2, 2);
	s.det = pow(s.b, 2) - (4 * s.a * s.c);
	if (s.det < 0)
		return ;
	s.t1 = (-s.b - sqrt(s.det)) / (2 * s.a);
	s.t2 = (-s.b + sqrt(s.det)) / (2 * s.a);
	if (s.t1 >= 0 && rt->t > s.t1)
		rt->t = s.t1;
	else if (s.t2 >= 0 && rt->t > s.t2)
		rt->t = s.t2;
}
