/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:56:12 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 12:12:11 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		intersect(double a, double b, double det)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(det)) / (2 * a);
	t2 = (-b + sqrt(det)) / (2 * a);
	return (t1 < t2 ? t1 : t2);
}

int			check_split(t_mini_rt *rt)
{
	int		i;
	int		j;

	i = 0;
	while (rt->split[i])
	{
		if (i != 0)
		{
			j = 0;
			while (rt->split[i][j])
			{
				if (!ft_isdigit(rt->split[i][j]) && rt->split[i][j] != ','
					&& rt->split[i][j] != '.')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (i);
}

void		free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_vec		split_vec(char *str, t_mini_rt *rt)
{
	t_vec 	v;
	char	**split;

	split = ft_split(str, ',');
	if (check_split(rt) < 3)
	{
		free_split(split);
		handle_error("invalid vector parsing", rt);
	}
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	free_split(split);
	return (v);
}

t_color		split_rgb(char *str, t_mini_rt *rt)
{
	t_color c;
	char	**split;

	split = ft_split(str, ',');
	if (check_split(rt) < 3)
	{
		free_split(split);
		handle_error("invalid rgb parsing", rt);
	}
	c.r = ft_atoi(split[0]);
	c.g = ft_atoi(split[1]);
	c.b = ft_atoi(split[2]);
	free_split(split);
	return (c);
}
