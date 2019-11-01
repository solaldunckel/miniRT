/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:56:12 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/01 16:05:04 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_strstr_rt(char *str, char *to_find)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[j] == to_find[j])
		{
			if (str[i + j + 1] == ' ' && to_find[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		rgt_to_color(int r, int g, int b)
{
	int				*color;
	unsigned char 	*tmp;

	color = NULL;
	tmp = (unsigned char *)color;
	tmp[1] = r;
	tmp[2] = g;
	tmp[3] = b;
	return ((int)color);
}

double	ft_atof(char *str)
{
	double	atof;
	int		atoi;
	int		prec;
	int		i;

	atoi = ft_atoi(str);
	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	i++;
	atof = ft_atoi(&str[i]);
	prec = ft_strlen(&str[i]);
	while (prec--)
		atof = atof / 10;
	return (atoi + atof);
}
