/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:36:45 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/02 15:11:50 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		key_hook5(int key, t_mini_rt *rt)
{
	if (key == KEY_DOWN && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.y--;
		rt->move_obj->point2.y--;
		rt->move_obj->point3.y--;
	}
	else if (key == KEY_LEFT && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.x--;
		rt->move_obj->point2.x--;
		rt->move_obj->point3.x--;
	}
	else if (key == KEY_RIGHT && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.x++;
		rt->move_obj->point2.x++;
		rt->move_obj->point3.x++;
	}
	else
		return (0);
	return (1);
}

int		key_hook4(int key, t_mini_rt *rt)
{
	if (key == KEY_N && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.z--;
		rt->move_obj->point2.z--;
		rt->move_obj->point3.z--;
	}
	else if (key == KEY_M && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.z++;
		rt->move_obj->point2.z++;
		rt->move_obj->point3.z++;
	}
	else if (key == KEY_UP && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.y++;
		rt->move_obj->point2.y++;
		rt->move_obj->point3.y++;
	}
	else if (key_hook5(key, rt))
		return (1);
	else
		return (0);
	return (1);
}

int		key_hook3(int key, t_mini_rt *rt)
{
	if (key == KEY_I && rt->move_obj)
		rt->move_obj->orient.y += 0.1;
	else if (key == KEY_K && rt->move_obj)
		rt->move_obj->orient.y -= 0.1;
	else if (key == KEY_J && rt->move_obj)
		rt->move_obj->orient.x -= 0.1;
	else if (key == KEY_L && rt->move_obj)
		rt->move_obj->orient.x += 0.1;
	else if (key == KEY_U && rt->move_obj)
		rt->move_obj->orient.z -= 0.1;
	else if (key == KEY_O && rt->move_obj)
		rt->move_obj->orient.z += 0.1;
	else if (key == KEY_N && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.z--;
	else if (key == KEY_M && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.z++;
	else if (key == KEY_G)
		rt->cam->orient.y -= 0.1;
	else
		return (0);
	if (rt->move_obj)
		check_orient(&rt->move_obj->orient);
	return (1);
}

int		key_hook2(int key, t_mini_rt *rt)
{
	if (key == KEY_T)
		rt->cam->orient.y += 0.1;
	else if (key == KEY_R)
		rt->cam->orient.z -= 0.1;
	else if (key == KEY_Y)
		rt->cam->orient.z += 0.1;
	else if (key == KEY_ENTER)
		select_objs(rt);
	else if (key == KEY_PIPE)
		unselect_obj(rt);
	else if (key == KEY_UP && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.y++;
	else if (key == KEY_DOWN && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.y--;
	else if (key == KEY_LEFT && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.x--;
	else if (key == KEY_RIGHT && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.x++;
	else if (key_hook3(key, rt))
		return (1);
	else if (key_hook4(key, rt))
		return (1);
	else
		return (0);
	return (1);
}

int		key_hook(int key, t_mini_rt *rt)
{
	if (key == KEY_W)
		rt->cam->pov.y++;
	else if (key == KEY_S)
		rt->cam->pov.y--;
	else if (key == KEY_A)
		rt->cam->pov.x--;
	else if (key == KEY_D)
		rt->cam->pov.x++;
	else if (key == KEY_Q)
		rt->cam->pov.z--;
	else if (key == KEY_E)
		rt->cam->pov.z++;
	else if (key == KEY_F)
		rt->cam->orient.x -= 0.1;
	else if (key == KEY_H)
		rt->cam->orient.x += 0.1;
	else if (key_hook2(key, rt))
		;
	else
		return (0);
	if (!check_orient(&rt->cam->orient))
		return (0);
	redraw_window(rt);
	return (1);
}
