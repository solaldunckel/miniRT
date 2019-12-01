/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/01 20:09:40 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		get_mouse_pos(int x, int y, t_mini_rt *rt)
{
	if (x > 0 && x <= rt->res.x && y > 0 && y < rt->res.y && rt->mouse)
	{
		if (x < rt->res.x / 3)
			rt->cam->orient.x -= 0.1;
		else if (x > rt->res.x - rt->res.x / 3)
			rt->cam->orient.x += 0.1;
		else if (y < rt->res.y / 3)
			rt->cam->orient.y -= 0.1;
		else if (y > rt->res.y - rt->res.y / 3)
			rt->cam->orient.y += 0.1;
		check_orient(&rt->cam->orient);
		redraw_window(rt);
	}
	return (1);
}

int		mouse_press(int button, int x, int y, t_mini_rt *rt)
{
	(void)x;
	(void)y;
	if (button == 1)
		rt->mouse = 1;
	return (1);
}

int		mouse_release(int button, int x, int y, t_mini_rt *rt)
{
	(void)x;
	(void)y;
	if (button == 1)
		rt->mouse = 0;
	return (1);
}
