/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:36:45 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/19 19:17:00 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	redraw_window(t_mini_rt *rt)
{
	int		i;

	i = 0;
	while (i < rt->cam->img.size_line * rt->res.y)
	{
		rt->cam->img.add[i] = 0;
		i++;
	}
	setup_rt(rt);
	raytracing(rt);
	mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->cam->img.ptr, 0, 0);
}

int		key_hook2(int key, t_mini_rt *rt)
{
	if (key == KEY_T)
		rt->cam->orient.y += 0.1;
	else if (key == KEY_R)
		rt->cam->orient.z -= 0.1;
	else if (key == KEY_Y)
		rt->cam->orient.z += 0.1;
	else
		return (0);
	return (1);
}

void	check_orient(t_vec *orient)
{
	if (orient->x > 1)
		orient->x = 1;
	if (orient->x < -1)
		orient->x = -1;
	if (orient->y > 1)
		orient->y = 1;
	if (orient->y < -1)
		orient->y = -1;
	if (orient->z > 1)
		orient->z = 1;
	if (orient->z < -1)
		orient->z = -1;
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
	else if (key == KEY_G)
		rt->cam->orient.y -= 0.1;
	else if (key_hook2(key, rt))
		;
	else
		return (0);
	check_orient(&rt->cam->orient);
	redraw_window(rt);
	return (1);
}

int		get_keypress(int key, t_mini_rt *rt)
{
	printf("%d\n", key);
	if (key == KEY_TAB)
		change_cam(rt);
	else if (key == KEY_ESC)
		exit_and_free(rt);
	key_hook(key, rt);
	return (1);
}
