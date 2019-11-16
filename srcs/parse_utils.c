/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:41:05 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 14:45:29 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	if (check_split(split) != 3)
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
	if (check_split(split) != 3)
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
