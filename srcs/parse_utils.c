/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:41:05 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/28 15:42:51 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			check_id_bonus(t_mini_rt *rt)
{
	if (ft_strequ(rt->split[0], "co"))
		parse_cone(rt);
	else if (ft_strequ(rt->split[0], "AA"))
		parse_antialiasing(rt);
	else if (ft_strequ(rt->split[0], "SEPIA"))
		rt->sepia = 1;
	else if (ft_strequ(rt->split[0], "st"))
		rt->st = 1;
	else if (ft_strequ(rt->split[0], "dl"))
		parse_dir_light(rt);
	else if (ft_strequ(rt->split[0], "cb"))
		parse_cube(rt);
	else
		return (0);
	return (1);
}

void		check_id(t_mini_rt *rt)
{
	if (ft_strequ(rt->split[0], "R"))
		parse_res(rt);
	else if (ft_strequ(rt->split[0], "A"))
		parse_ambient(rt);
	else if (ft_strequ(rt->split[0], "c"))
		parse_camera(rt);
	else if (ft_strequ(rt->split[0], "l"))
		parse_light(rt);
	else if (ft_strequ(rt->split[0], "sp"))
		parse_sphere(rt);
	else if (ft_strequ(rt->split[0], "pl"))
		parse_plane(rt);
	else if (ft_strequ(rt->split[0], "sq"))
		parse_square(rt);
	else if (ft_strequ(rt->split[0], "cy"))
		parse_cylindre(rt);
	else if (ft_strequ(rt->split[0], "tr"))
		parse_triangle(rt);
	else if (rt->split[0][0] == '#' || ft_strequ(rt->split[0], "#"))
		;
	else if (check_id_bonus(rt))
		;
	else
		handle_error("unrecognized id", rt);
}

int			check_split(char **split)
{
	int		i;
	int		j;

	i = 0;
	while (split[i])
	{
		if (i != 0)
		{
			j = 0;
			while (split[i][j])
			{
				if (!ft_isdigit(split[i][j]) && split[i][j] != ','
					&& split[i][j] != '.' && split[i][j] != '-')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (i);
}

t_vec		split_vec(char *str, t_mini_rt *rt, int orient)
{
	t_vec	v;
	char	**split;

	split = ft_split(str, ',');
	if (check_split(split) != 3 || ft_str_c_count(str, ',') != 2)
	{
		free_split(split);
		handle_error("invalid vector parsing", rt);
	}
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	free_split(split);
	if (orient && (v.x > 1 || v.y > 1 || v.z > 1 || v.x < -1 || v.y < -1
		|| v.z < -1))
		handle_error("invalid vector parsing", rt);
	return (v);
}

t_color		split_rgb(char *str, t_mini_rt *rt)
{
	t_color c;
	char	**split;

	split = ft_split(str, ',');
	if (check_split(split) != 3 || ft_str_c_count(str, ',') != 2)
	{
		free_split(split);
		handle_error("invalid rgb parsing", rt);
	}
	c.r = ft_atof(split[0]) / 255;
	c.g = ft_atof(split[1]) / 255;
	c.b = ft_atof(split[2]) / 255;
	free_split(split);
	if (c.r > 1 || c.g > 1 || c.b > 1 || c.r < 0 || c.g < 0 || c.b < 0)
		handle_error("invalid rgb parsing", rt);
	return (c);
}
