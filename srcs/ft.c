/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:56:12 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/14 14:41:28 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		check_extension(t_mini_rt *rt, char *rt_file)
{
	int		i;

	i = ft_strlen(rt_file) - 1;
	if (rt_file[i] != 't' || rt_file[i - 1] != 'r' || rt_file[i - 2] != '.')
		handle_error("wrong file extension", rt);
}

int			intersect(double a, double b, double det)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(det)) / (2 * a);
	t2 = (-b + sqrt(det)) / (2 * a);
	if (t1 < t2)
		return (t1);
	if (t1 > t2)
		return (t2);
	return (t1);
}
