/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:59:28 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 11:24:32 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_element(void *elem)
{
	t_element 	*tmp;

	tmp = elem;
	free(tmp->id);
	free(tmp);
}

void	show_id(void *lst)
{
	t_list		*tmp;
	t_element 	*elem;

	tmp = lst;
	elem = tmp->content;
	ft_printf("%s\n", elem->id);
}

int		parse_rt_file(char *rt_file, t_mini_rt *rt)
{
	int		fd;
	int		ret;

	ret = 0;
	if ((fd = open(rt_file, O_RDONLY)) < 0)
		handle_error("fail to open scene file", rt);
	while (get_next_line(fd, &rt->line) > 0)
	{
		rt->i = 0;
		while (!ft_isalpha(rt->line[rt->i]))
			rt->i++;
		ret = ft_strstr_rt(&rt->line[rt->i], "R", rt) ? parse_res(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "A", rt) ? parse_ambient(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "c", rt) ? parse_camera(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "l", rt) ? parse_light(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "sp", rt) ? parse_sphere(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "pl", rt) ? parse_plane(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "sq", rt) ? parse_square(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "cy", rt) ? parse_cylindre(rt) : 1;
		ret = ft_strstr_rt(&rt->line[rt->i], "tr", rt) ? parse_triangle(rt) : 1;
		ft_strdel(&rt->line);
		if (!ret)
			return (0);
	}
	return (1);
}

int		start_mini_rt(t_mini_rt *rt, char **argv)
{
	rt->list = NULL;
	if (!(parse_rt_file(argv[1], rt)))
		handle_error("fail to parse file", rt);
	if (!(rt->mlx_ptr = mlx_init()))
		handle_error("fail to init mlx", rt);
	if (!(rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->res.x, rt->res.y, argv[0])))
		handle_error("fail to create windows", rt);
	if (!(rt->img.ptr = mlx_new_image(rt->mlx_ptr, rt->res.x, rt->res.y)))
		handle_error("fail to create image", rt);
	rt->img.add = mlx_get_data_addr(rt->img.ptr, &rt->img.bbp,
		&rt->img.size_line, &rt->img.endian);
	ft_printf("" BOLDGREEN "Loading miniRT...\n" RESET);
	// ft_printf("list size : %d\n", ft_lstsize(rt->list));
	// ft_lstiter(rt->list, show_id);
	// // function to draw
	mlx_key_hook(rt->win_ptr, get_keypress, rt);
	mlx_hook(rt->win_ptr, 17, 0, exit_and_free, rt);
	mlx_loop(rt->mlx_ptr);
	return (1);
}

int		main(int argc, char **argv)
{
	t_mini_rt	rt;

	if (argc > 3 || argc == 1 || (argc == 3 && !ft_strequ(argv[2], "-save")))
		handle_error("wrong arguments", &rt);
	if (argc == 3 && ft_strequ(argv[2], "-save"))
		start_mini_rt(&rt, argv);
	if (argc == 2)
		start_mini_rt(&rt, argv);
	return (0);
}
