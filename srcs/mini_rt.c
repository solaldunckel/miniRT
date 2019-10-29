/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:59:28 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/29 16:57:22 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_rt_file(char *rt_file, t_mini_rt *rt)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	if ((fd = open(rt_file, O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line))
	{
		while (line[i])
		{
			if (line[i] == 'R')
			{
				i++;
				rt->res_x = ft_atoi(&line[i]);
				i += ft_intlen(rt->res_x) + 1;
				rt->res_y = ft_atoi(&line[i]);
			}
			i++;
		}
		printf("%s\n", line);
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
		if (!(rt.win_ptr = mlx_new_window(rt.mlx_ptr, 1920, 1080, argv[0])))
			return (0);
		mlx_loop(rt.mlx_ptr);
		parse_rt_file(argv[argc - 1], &rt);
	}
	return (0);
}
