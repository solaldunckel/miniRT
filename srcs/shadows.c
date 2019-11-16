/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 23:24:13 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 02:53:20 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void			find_shadow(t_mini_rt *rt, t_element *obj, t_vec ori, t_vec dir)
{
	if (obj->id == SPHERE)
		sphere(rt, obj, ori, dir);
	else if (obj->id == PLANE)
		plane(rt, obj, ori, dir);
	else if (obj->id == CYLINDER)
		cylinder(rt, obj, ori, dir);
	else if (obj->id == CIRCLE)
		circle(rt, obj, ori, dir);
	else if (obj->id == SQUARE)
		circle(rt, obj, ori, dir);
}

int				apply_shadows(t_mini_rt *rt, t_vec ori, t_vec dir)
{
	t_list		*tmp;
	t_element	*obj;
	t_element	*save;

	save = rt->obj;
	//rt->obj = NULL;
	tmp = rt->objs_list;
	rt->t = INT_MAX;
	rt->k = INT_MAX;
	while (tmp)
	{
		obj = tmp->content;
		if (save == obj)
		{
			//save->id == CYLINDER ? tmp = tmp->next->next : 0;
			tmp = tmp->next;
			continue ;
		}
		find_shadow(rt, tmp->content, ori, dir);
		if (rt->t > 0 && rt->t < rt->k)
		{
			rt->k = rt->t;
			rt->obj2 = tmp->content;
		}
		tmp = tmp->next;
	}
	if (rt->obj2 != NULL)
		return (0);
	return (1);
}
