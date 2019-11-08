/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:59:28 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 14:52:04 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	handle_error()
{
	ft_printf("Error\n");
	exit(0);
}

int		parse_rt_file(char *rt_file, t_mini_rt *rt)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	if ((fd = open(rt_file, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line))
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
		if (!ret)
			return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_mini_rt	rt;

	if (argc > 3)
		return (0);
	if (argc == 3 && !ft_strcmp(argv[argc - 1], "-save"))
		return (1); // save
	if (argc == 2)
	{
		if (!(rt.mlx_ptr = mlx_init()))
			return (0);
		if (!(parse_rt_file(argv[argc - 1], &rt)))
			handle_error();
		if (!(rt.win_ptr = mlx_new_window(rt.mlx_ptr, rt.res.x, rt.res.y, argv[0])))
			return (0);
		//mlx_loop(rt.mlx_ptr);
	}
	return (0);
}
