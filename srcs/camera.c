/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:41:47 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/12 13:46:39 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	select_cam(t_mini_rt *rt)
{
	t_list		*tmp;
	int			count;

	count = 0;
	tmp = rt->cam_list;
	while (tmp)
	{
		if (rt->cur_cam == count)
		{
			rt->cam = tmp->content;
			rt->cur_cam++;
			if (rt->cur_cam == rt->cam_count)
				rt->cur_cam = 0;
			return ;
		}
		count++;
		tmp = tmp->next;
	}
}

void	change_cam(t_mini_rt *rt)
{
	rt->img.add = NULL;
	free(rt->img.add);
	mlx_destroy_image(rt->mlx_ptr, rt->img.ptr);
	if (!(rt->img.ptr = mlx_new_image(rt->mlx_ptr, rt->res.x, rt->res.y)))
		return ;
	if (!(rt->img.add = mlx_get_data_addr(rt->img.ptr, &rt->img.bpp,
		&rt->img.size_line, &rt->img.endian)))
		return ;
	mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
	select_cam(rt);
	setup_rt(rt);
	raytracing(rt);
	mlx_key_hook(rt->win_ptr, get_keypress, rt);
	mlx_hook(rt->win_ptr, 17, 0, exit_and_free, rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img.ptr, 0, 0);
	mlx_loop(rt->mlx_ptr);
}
