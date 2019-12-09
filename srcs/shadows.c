/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 23:24:13 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/03 15:27:33 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		apply_shadows(t_mini_rt *rt, t_vec ori, t_vec dir, t_element *light)
{
	t_list		*tmp;
	t_element	*obj;

	tmp = rt->objs_list;
	rt->t = INT_MAX;
	plane(rt, light, ori, dir);
	rt->k = rt->t - 0.1;
	while (tmp)
	{
		obj = tmp->content;
		if (rt->obj == obj)
		{
			rt->obj->id == CYLINDER ? tmp = tmp->next->next : 0;
			rt->obj->id == CONE ? tmp = tmp->next : 0;
			tmp = tmp->next;
			continue ;
		}
		find_objs(rt, tmp->content, ori, dir);
		if (rt->t > 0 && rt->t < rt->k)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
