/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:56:12 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 15:18:10 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	multi_thread(rt);
	mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->cam->img.ptr, 0, 0);
}
