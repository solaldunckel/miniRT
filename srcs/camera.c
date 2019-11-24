/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:41:47 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/23 18:31:41 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	create_all_cam(t_mini_rt *rt)
{
	t_list		*tmp;
	int			count;

	count = 1;
	tmp = rt->cam_list;
	while (tmp)
	{
		rt->cam = tmp->content;
		if (!(rt->cam->img.ptr = mlx_new_image(rt->mlx_ptr, rt->res.x,
			rt->res.y)))
			handle_error("fail to create Minilibx image", rt);
		if (!(rt->cam->img.add = mlx_get_data_addr(rt->cam->img.ptr,
			&rt->cam->img.bpp, &rt->cam->img.size_line, &rt->cam->img.endian)))
			handle_error("fail to get Minilibx image data", rt);
		setup_rt(rt);
		multi_thread(rt);
		if (count++ && rt->save)
			return ;
		rt->cam_count > 1 ? ft_printf("" BOLDGREEN "-> %d/%d"
			" camera rendered ! <-\n" RESET, count - 1, rt->cam_count) : 0;
		tmp = tmp->next;
	}
}

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
	if (rt->cam_count > 1)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		select_cam(rt);
		mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->cam->img.ptr,
			0, 0);
	}
}
