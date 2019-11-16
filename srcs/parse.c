/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 01:33:27 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_rt_file(char *rt_file, t_mini_rt *rt)
{
	int		fd;

	if ((fd = open(rt_file, O_RDONLY)) < 0)
		handle_error("fail to open scene file", rt);
	while (get_next_line(fd, &rt->line) > 0)
	{
		rt->split = ft_ssplit(rt->line, " \t\v\n\r\f");
		ft_strequ(rt->split[0], "R") ? parse_res(rt) : 0;
		ft_strequ(rt->split[0], "A") ? parse_ambient(rt) : 0;
		ft_strequ(rt->split[0], "c") ? parse_camera(rt) : 0;
		ft_strequ(rt->split[0], "l") ? parse_light(rt) : 0;
		ft_strequ(rt->split[0], "sp") ? parse_sphere(rt) : 0;
		ft_strequ(rt->split[0], "pl") ? parse_plane(rt) : 0;
		ft_strequ(rt->split[0], "sq") ? parse_square(rt) : 0;
		ft_strequ(rt->split[0], "cy") ? parse_cylindre(rt) : 0;
		ft_strequ(rt->split[0], "tr") ? parse_triangle(rt) : 0;
		rt->split = free_split(rt->split);
		ft_strdel(&rt->line);
	}
	close(fd);
	if (!(rt->cam_count = ft_lstsize(rt->cam_list)))
		handle_error("no camera available", rt);
	if (!rt->res.x || !rt->res.y)
		handle_error("no resolution", rt);
}

int		parse_res(t_mini_rt *rt)
{
	if (check_split(rt->split) != 3)
		handle_error("invalid resolution", rt);
	rt->res.x = ft_atoi(rt->split[1]);
	rt->res.y = ft_atoi(rt->split[2]);
	if (rt->res.x < 1 || rt->res.y < 1)
		handle_error("resolution too small", rt);
	rt->res.x > 2560 ? rt->res.x = 2560 : 0;
	rt->res.y > 1440 ? rt->res.y = 1395 : 0;
	return (1);
}

int		parse_ambient(t_mini_rt *rt)
{
	if (check_split(rt->split) != 3)
		handle_error("invalid ambient light", rt);
	rt->ambient.ratio = ft_atof(rt->split[1]);
	rt->ambient.color = split_rgb(rt->split[2], rt);
	if (rt->ambient.ratio > 1 || rt->ambient.ratio < 0)
		handle_error("invalid ambient light", rt);
	return (1);
}

int		parse_camera(t_mini_rt *rt)
{
	t_camera		*camera;

	if (!(camera = ft_calloc(1, sizeof(t_camera))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 3)
	{
		free(camera);
		handle_error("camera parsing error", rt);
	}
	camera->pov = split_vec(rt->split[1], rt, 0);
	camera->orient = split_vec(rt->split[2], rt, 1);
	ft_lstadd_back(&rt->cam_list, ft_lstnew(camera));
	return (1);
}

int		parse_light(t_mini_rt *rt)
{
	t_element		*light;

	if (!(light = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (check_split(rt->split) != 4)
	{
		free(light);
		handle_error("light parsing error", rt);
	}
	light->point = split_vec(rt->split[1], rt, 0);
	light->ratio = ft_atof(rt->split[2]);
	light->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->light_list, ft_lstnew(light));
	if (light->ratio > 1 || light->ratio < 0)
		handle_error("light parsing error", rt);
	return (1);
}
