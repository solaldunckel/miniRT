/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:59:28 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/10 23:31:08 by sdunckel         ###   ########.fr       */
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
			return;
		}
		count++;
		tmp = tmp->next;
	}
}

int		init_mlx(t_mini_rt *rt)
{
	if (!(rt->mlx_ptr = mlx_init()))
		return (0);
	if (!(rt->img.ptr = mlx_new_image(rt->mlx_ptr, rt->res.x, rt->res.y)))
		return (0);
	if (!(rt->img.add = mlx_get_data_addr(rt->img.ptr, &rt->img.bpp,
		&rt->img.size_line, &rt->img.endian)))
		return (0);
	if (!rt->save && !(rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->res.x,
		rt->res.y, "miniRT")))
		return (0);
	ft_printf("" BOLDGREEN "Minilibx successfully initialized !\n" RESET);
	return (1);
}

void	start_mini_rt(t_mini_rt *rt)
{
	if (!(init_mlx(rt)))
		handle_error("fail to initialize Minilibx", rt);
	ft_printf("" BOLDGREEN "Loading miniRT...\n" RESET);
	select_cam(rt);
	raytracing(rt);
	if (rt->save)
	{
		create_bmp_image(rt, BMP_FILE_NAME);
		ft_printf("" BOLDGREEN ">>>> " BMP_FILE_NAME " exported <<<<\n" RESET);
		exit_and_free(rt);
	}
	mlx_key_hook(rt->win_ptr, get_keypress, rt);
	mlx_hook(rt->win_ptr, 17, 0, exit_and_free, rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img.ptr, 0, 0);
	mlx_loop(rt->mlx_ptr);
}

void	init_rt(t_mini_rt *rt)
{
	rt->mlx_ptr = NULL;
	rt->win_ptr = NULL;
	rt->elem_list = NULL;
	rt->cam_list = NULL;
	rt->light_list = NULL;
	rt->cur_cam = 0;
	rt->cam = NULL;
	rt->obj = NULL;
	rt->col = 0x000000;
	rt->t = 0;
	rt->save = 0;
}

int		main(int argc, char **argv)
{
	t_mini_rt	rt;

	init_rt(&rt);
	if (argc > 3 || argc == 1 || (argc == 3 && !ft_strequ(argv[2], "-save")))
		handle_error("wrong arguments", &rt);
	if (argc == 3 && ft_strequ(argv[2], "-save"))
	{
		if (!(parse_rt_file(argv[1], &rt)))
			handle_error("fail to parse the scene", &rt);
		rt.save = 1;
		start_mini_rt(&rt);
	}
	if (argc == 2)
	{
		if (!(parse_rt_file(argv[1], &rt)))
			handle_error("fail to parse the scene", &rt);
		start_mini_rt(&rt);
	}
	return (0);
}
