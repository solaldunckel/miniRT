/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:59:28 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 12:32:13 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		handle_error(char *str)
{
	ft_printf("miniRT Error: %s\n", str);
	exit(0);
	return (0);
}

int		parse_rt_file(char *rt_file, t_mini_rt *rt)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	if ((fd = open(rt_file, O_RDONLY)) < 0)
		return (handle_error("fail to open scene"));
	while (get_next_line(fd, &line) > 0)
	{
		rt->i = 0;
		while (!ft_isalpha(line[rt->i]))
			rt->i++;
		ret = ft_strstr_rt(&line[rt->i], "R") ? parse_res(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "A") ? parse_ambient(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "c") ? parse_camera(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "l") ? parse_light(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "sp") ? parse_sphere(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "pl") ? parse_plane(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "sq") ? parse_square(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "cy") ? parse_cylindre(rt, line) : 1;
		ret = ft_strstr_rt(&line[rt->i], "tr") ? parse_triangle(rt, line) : 1;
		ft_strdel(&line);
		if (!ret)
			return (0);
	}
	return (1);
}

int		get_keypress(int key, t_mini_rt *rt)
{
	(void)rt;
	if (key == 65307)
		exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_mini_rt	rt;
	int			x;
	int			y;

	if (argc > 3)
		return (0);
	if (argc == 3 && !ft_strcmp(argv[2], "-save"))
		return (1); // save
	if (argc == 2)
	{
		if (!(rt.mlx_ptr = mlx_init()))
			return (handle_error("fail to init mlx"));
		if (!(parse_rt_file(argv[1], &rt)))
			handle_error("fail to parse file");
		if (!(rt.image_ptr = mlx_new_image(rt.mlx_ptr, rt.res.x, rt.res.y)))
			handle_error("fail to create image");
		if (!(rt.win_ptr = mlx_new_window(rt.mlx_ptr, rt.res.x, rt.res.y, argv[0])))
			return (handle_error("fail to create windows"));
		mlx_key_hook(rt.win_ptr, &get_keypress, &rt);
		mlx_loop(rt.mlx_ptr);
	}
	return (0);
}
