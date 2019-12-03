/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:55:13 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/03 15:39:42 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	create_circle(t_mini_rt *rt, t_element *cylinder, float t, int create)
{
	t_element		*circle;

	if (!(circle = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	circle->id = 6;
	circle->nm = 1;
	circle->point = vec_add(cylinder->point,
		vec_mul(vec_normalize(cylinder->orient), t));
	circle->orient = cylinder->orient;
	circle->diameter = cylinder->diameter;
	circle->color = cylinder->color;
	circle->ref = cylinder->ref;
	circle->rainbow = cylinder->rainbow;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(circle));
	if (create)
		create_circle(rt, cylinder, cylinder->height / -2, 0);
}

void	circle(t_mini_rt *rt, t_element *circle, t_vec ori, t_vec dir)
{
	t_solve s;
	t_vec	inter;

	s.a = vec_dot(vec_sub(ori, circle->point), circle->orient);
	s.b = vec_dot(dir, circle->orient);
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return ;
	s.t1 = -s.a / s.b;
	if (s.t1 < 0 || rt->t < s.t1)
		return ;
	inter = vec_add(ori, vec_mul(dir, s.t1));
	inter = vec_sub(inter, circle->point);
	s.det = sqrt(vec_dot(inter, inter));
	s.det <= circle->diameter / 2 ? rt->t = s.t1 : 0;
}
