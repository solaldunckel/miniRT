/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2020/01/18 07:06:47 by sdunckel         ###   ########.fr       */
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
		if (rt->split[0])
			check_id(rt);
		rt->split = free_split(rt->split);
		ft_strdel(&rt->line);
	}
	close(fd);
	rt->obj_count = objs_count(rt->objs_list);
	if (!(rt->cam_count = ft_lstsize(rt->cam_list)))
		handle_error("no camera available", rt);
	if (!rt->res.parsed)
		handle_error("no resolution", rt);
}

void	parse_res(t_mini_rt *rt)
{
	if (count_split(rt->split) != 3 || !check_split(rt->split, 0))
		handle_error("invalid resolution", rt);
	rt->res.x = ft_atoi(rt->split[1]);
	rt->res.y = ft_atoi(rt->split[2]);
	if (rt->res.x < 1 || rt->res.y < 1)
		handle_error("resolution too small", rt);
	rt->res.parsed = 1;
	rt->res.x > 2560 ? rt->res.x = 2560 : 0;
	rt->res.y > 1440 ? rt->res.y = 1395 : 0;
}

void	parse_ambient(t_mini_rt *rt)
{
	if (count_split(rt->split) != 3 || !check_split(rt->split, 0))
		handle_error("invalid ambient light", rt);
	rt->ambient.ratio = ft_atof(rt->split[1]);
	rt->ambient.color = split_rgb(rt->split[2], rt);
	if (rt->ambient.ratio > 1 || rt->ambient.ratio < 0)
		handle_error("invalid ambient light", rt);
	rt->ambient.parsed = 1;
}

void	parse_camera(t_mini_rt *rt)
{
	t_camera		*camera;

	if (!(camera = ft_calloc(1, sizeof(t_camera))))
		handle_error("fail to malloc", rt);
	if (count_split(rt->split) != 3 || !check_split(rt->split, 0))
	{
		free(camera);
		handle_error("camera parsing error", rt);
	}
	camera->pov = split_vec(rt->split[1], rt, 0);
	camera->orient = split_vec(rt->split[2], rt, 1);
	ft_lstadd_back(&rt->cam_list, ft_lstnew(camera));
}

void	parse_light(t_mini_rt *rt)
{
	t_element		*light;

	if (!(light = ft_calloc(1, sizeof(t_element))))
		handle_error("fail to malloc", rt);
	if (count_split(rt->split) != 4 || !check_split(rt->split, 0))
	{
		free(light);
		handle_error("light parsing error", rt);
	}
	light->id = 10;
	light->point = split_vec(rt->split[1], rt, 0);
	light->ratio = ft_atof(rt->split[2]);
	light->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->light_list, ft_lstnew(light));
	if (light->ratio > 1 || light->ratio < 0)
		handle_error("light parsing error", rt);
}
