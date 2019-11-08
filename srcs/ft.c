/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:56:12 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/07 14:10:40 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_strstr_rt(char *str, char *to_find, t_mini_rt *rt)
{
	size_t		j;

	j = 0;
	while (str[j] == to_find[j])
	{
		rt->i++;
		if (str[j + 1] == ' ' && to_find[j + 1] == '\0')
			return (1);
		j++;
	}
	rt->i -= j;
	return (0);
}

int		ft_atoi_rt(char *str, t_mini_rt *rt)
{
	int		atoi;
	int		negative;

	atoi = 0;
	negative = 0;
	while (ft_is_space(str[rt->i]))
		rt->i++;
	if (str[rt->i] == ',')
		rt->i++;
	if (str[rt->i] == '-' || str[rt->i] == '+')
	{
		if (str[rt->i] == '-')
			negative = 1;
		rt->i++;
	}
	while (str[rt->i] >= '0' && str[rt->i] <= '9')
	{
		atoi = atoi * 10 + str[rt->i] - 48;
		rt->i++;
	}
	return (negative ? -atoi : atoi);
}

double	ft_atof_rt(char *str, t_mini_rt *rt)
{
	double	atof;
	int		atoi;
	int		prec;

	atoi = ft_atoi_rt(str, rt);
	if (str[rt->i] != '.')
		return (atoi);
	rt->i++;
	atof = ft_atoi_rt(str, rt);
	prec = ft_intlen(atof);
	while (prec--)
		atof = atof / 10;
	return (atoi + atof);
}
