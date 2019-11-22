/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:41:05 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 17:59:59 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	else if (ft_strequ(rt->split[0], "co"))
		parse_cone(rt);
	else if (ft_strequ(rt->split[0], "tr"))
		parse_triangle(rt);
	else if (ft_strequ(rt->split[0], "AA"))
		parse_antialiasing(rt);
	else if (ft_strequ(rt->split[0], "SEPIA"))
		rt->sepia = 1;
	// else
	// 	handle_error("unrecognized id", rt);
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

char		**free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	free(split);
	split = NULL;
	return (split);
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
	c.r = ft_atoi(split[0]);
	c.g = ft_atoi(split[1]);
	c.b = ft_atoi(split[2]);
	free_split(split);
	if (c.r > 255 || c.g > 255 || c.b > 255 || c.r < 0 || c.g < 0 || c.b < 0)
		handle_error("invalid rgb parsing", rt);
	return (c);
}
