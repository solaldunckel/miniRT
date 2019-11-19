/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 23:24:13 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/19 12:27:19 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int				apply_shadows(t_mini_rt *rt, t_vec ori, t_vec dir)
{
	t_list		*tmp;
	t_element	*obj;
	t_element	*save;

	save = rt->obj;
	//rt->obj = NULL;
	tmp = rt->objs_list;
	rt->t = INT_MAX;
	while (tmp)
	{
		obj = tmp->content;
		if (save == obj || (save->id == CYLINDER && obj->id == CIRCLE))
		{
			tmp = tmp->next;
			continue ;
		}
		find_objs(rt, tmp->content, ori, dir);
		if (rt->t > 0 && rt->t != INT_MAX)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
