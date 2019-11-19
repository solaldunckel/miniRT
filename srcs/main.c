/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:59:28 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/19 17:50:54 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	init_rt(t_mini_rt *rt)
{
	rt->mlx_ptr = NULL;
	rt->win_ptr = NULL;
	rt->objs_list = NULL;
	rt->cam_list = NULL;
	rt->light_list = NULL;
	rt->line = NULL;
	rt->split = NULL;
	rt->cam = NULL;
	rt->cam_count = 0;
	rt->cur_cam = 0;
	rt->obj = NULL;
	rt->res.x = 0;
	rt->res.y = 0;
	rt->save = 0;
	rt->sepia = 0;
	rt->anti_aliasing = 1;
}

void	setup_rt(t_mini_rt *rt)
{
	rt->cam->fov = 70;
	rt->ray.ori = VEC_CREATE(rt->cam->pov.x, rt->cam->pov.y, rt->cam->pov.z);
	rt->aspect = (double)rt->res.x / (double)rt->res.y;
	if (rt->cam->orient.x != 0 || rt->cam->orient.z != 0)
		rt->cam->up = vec_normalize(vec_add(VEC_CREATE(0, -0.7, 0),
		rt->cam->orient));
	else
		rt->cam->up = vec_normalize(vec_add(VEC_CREATE(0, 0, -0.7),
		rt->cam->orient));
	rt->cam->right = vec_normalize(vec_cross(rt->cam->orient, rt->cam->up));
	rt->cam->up = vec_normalize(vec_cross(rt->cam->right, rt->cam->orient));
	rt->k = 0;
	rt->t = 0;
}

void	create_window(t_mini_rt *rt)
{
	if (!(rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->res.x,
		rt->res.y, "miniRT")))
		handle_error("fail to create Minilibx window", rt);
	mlx_key_hook(rt->win_ptr, get_keypress, rt);
	mlx_hook(rt->win_ptr, 17, 0, exit_and_free, rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->cam->img.ptr, 0, 0);
	mlx_loop(rt->mlx_ptr);
}

void	start_mini_rt(t_mini_rt *rt)
{
	if (!(rt->mlx_ptr = mlx_init()))
		handle_error("fail to initialize Minilibx", rt);
	ft_printf("" BOLDGREEN "Rendering miniRT...\n" RESET);
	create_all_cam(rt);
	select_cam(rt);
	if (rt->save)
	{
		create_bmp_image(rt, BMP_FILE_NAME);
		ft_printf("" BOLDGREEN ">> " BMP_FILE_NAME " exported <<\n" RESET);
		exit_and_free(rt);
	}
	create_window(rt);
}

int		main(int argc, char **argv)
{
	t_mini_rt	rt;

	init_rt(&rt);
	if (argc > 3 || argc == 1 || (argc == 3 && !ft_strequ(argv[2], "-save")))
		handle_error("wrong arguments", &rt);
	if (argc == 3 && ft_strequ(argv[2], "-save"))
		rt.save = 1;
	check_extension(&rt, argv[1]);
	parse_rt_file(argv[1], &rt);
	start_mini_rt(&rt);
	return (1);
}
