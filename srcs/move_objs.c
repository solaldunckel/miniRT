/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 09:55:14 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/26 19:27:13 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		objs_count(t_list *lst)
{
	int			count;
	t_list		*tmp;
	t_element	*obj;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		obj = tmp->content;
		tmp = tmp->next;
		if (obj->id != CIRCLE)
			count++;
	}
	return (count);
}

void	color_move_obj(t_mini_rt *rt, int reset)
{
	if (reset)
	{
		rt->move_obj->color.r = rt->tmp_color.r;
		rt->move_obj->color.g = rt->tmp_color.g;
		rt->move_obj->color.b = rt->tmp_color.b;
	}
	else
	{
		rt->tmp_color.r = rt->move_obj->color.r;
		rt->tmp_color.g = rt->move_obj->color.g;
		rt->tmp_color.b = rt->move_obj->color.b;
		rt->move_obj->color.r = fabs(rt->move_obj->color.r - 1);
		rt->move_obj->color.g = fabs(rt->move_obj->color.g - 1);
		rt->move_obj->color.b = fabs(rt->move_obj->color.b - 1);
	}
}

void	unselect_obj(t_mini_rt *rt)
{
	if (rt->move_obj)
		color_move_obj(rt, 1);
	rt->cur_obj = 0;
	rt->move_obj = NULL;
}

void	select_objs(t_mini_rt *rt)
{
	t_list		*tmp;
	int			count;

	count = 0;
	tmp = rt->objs_list;
	while (tmp)
	{
		if (rt->cur_obj == count)
		{
			if (rt->move_obj)
				color_move_obj(rt, 1);
			rt->move_obj = tmp->content;
			rt->cur_obj++;
			color_move_obj(rt, 0);
			if (rt->cur_obj == rt->obj_count)
				rt->cur_obj = 0;
			return ;
		}
		count++;
		tmp = tmp->next;
	}
}
