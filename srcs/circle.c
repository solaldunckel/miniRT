/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:55:13 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/23 18:55:58 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	circle(t_mini_rt *rt, t_element *circle, t_vec ori, t_vec dir)
{
	float	a;
	float	b;
	float	t;
	float	f;
	t_vec	inter;

	a = vec_dot(vec_sub(ori, circle->point), circle->orient);
	b = vec_dot(dir, circle->orient);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return ;
	t = -a / b;
	if (t < 0 || rt->t < t)
		return ;
	inter = vec_add(ori, vec_mul(dir, t));
	inter = vec_sub(inter, circle->point);
	f = vec_dot(inter, inter);
	sqrt(f) <= circle->diameter / 2 ? rt->t = t : 0;
}
