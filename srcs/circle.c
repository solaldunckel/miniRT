/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:55:13 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 21:55:14 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	circle(t_mini_rt *rt, t_element *circle, t_vec ori, t_vec dir)
{
	double	a;
	double	b;
	double	t;
	double	f;
	t_vec	inter;

	a = VEC_ADD(vec_dot(vec_sub(ori, circle->point), circle->orient));
	b = VEC_ADD(vec_dot(dir, circle->orient));
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return ;
	t = -a / b;
	if (t < 0 || rt->t < t)
		return ;
	inter = vec_add(ori, vec_mul(dir, t));
	inter = vec_sub(inter, circle->point);
	f = VEC_ADD(vec_dot(inter, inter));
	sqrt(f) <= circle->diameter / 2 ? rt->t = t : 0;
}
