/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:59:28 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/06 19:45:31 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	multi_thread(t_mini_rt *rt)
{
	int			i;
	pthread_t	thr[THREAD_COUNT];
	t_thread	thread[THREAD_COUNT];

	i = 0;
	while (i < THREAD_COUNT)
	{
		thread[i].cur_thr = i;
		ft_memcpy(&thread[i].scene, rt, sizeof(t_mini_rt));
		thread[i].scene.tr = i;
		pthread_create(&thr[i], NULL, (void*)raytracing, &thread[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(thr[i], NULL);
		i++;
	}
}

void	setup_rt(t_mini_rt *rt)
{
	if (!rt->anti_aliasing)
		rt->anti_aliasing = 1;
	rt->ray.ori = (t_vec){rt->cam->pov.x, rt->cam->pov.y, rt->cam->pov.z};
	rt->aspect = (float)rt->res.x / (float)rt->res.y;
	if (rt->cam->orient.x != 0 || rt->cam->orient.z != 0)
		rt->cam->up = vec_normalize(vec_add((t_vec){0, -1, 0},
		rt->cam->orient));
	else
		rt->cam->up = vec_normalize(vec_add((t_vec){0, 0, -1},
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
	mlx_hook(rt->win_ptr, 2, 0, get_keypress, rt);
	mlx_hook(rt->win_ptr, 4, 0, mouse_press, rt);
	mlx_hook(rt->win_ptr, 5, 0, mouse_release, rt);
	mlx_hook(rt->win_ptr, 6, 0, get_mouse_pos, rt);
	mlx_hook(rt->win_ptr, 17, 0, exit_and_free, rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->cam->img.ptr, 0, 0);
	mlx_loop(rt->mlx_ptr);
}

void	start_mini_rt(t_mini_rt *rt)
{
	ft_printf("" BOLDGREEN "Rendering miniRT...\n" RESET);
	create_all_cam(rt);
	select_cam(rt);
	if (rt->save)
	{
		create_bmp_image(rt, BMP_FILE_NAME);
		ft_printf("" BOLDGREEN ">> " BMP_FILE_NAME " exported <<\n" RESET);
		exit_and_free(rt);
	}
	ft_printf("" BOLDGREEN "Creating window...\n" RESET);
	create_window(rt);
}

int		main(int argc, char **argv)
{
	t_mini_rt	rt;

	ft_bzero(&rt, sizeof(t_mini_rt));
	if (!(rt.mlx_ptr = mlx_init()))
		handle_error("fail to initialize Minilibx", &rt);
	if (argc > 3 || argc == 1 || (argc == 3 && !ft_strequ(argv[2], "-save")))
		handle_error("wrong arguments", &rt);
	if (argc == 3 && ft_strequ(argv[2], "-save"))
		rt.save = 1;
	if (!ft_str_end(argv[1], ".rt"))
		handle_error("wrong file extension", &rt);
	parse_rt_file(argv[1], &rt);
	start_mini_rt(&rt);
	return (1);
}
