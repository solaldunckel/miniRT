/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:04:25 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 16:07:28 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		convert_rgb(t_color color)
{
	return (((color.r & 0xff) << 16) + ((color.g & 0xff) << 8)
	+ (color.b & 0xff));
}

int		color_put(t_mini_rt *rt, int x, int y)
{
	int i;

	i = y * rt->img.size_line + rt->img.bpp / 8 * x;
	if (i < 1)
		return (0);
	rt->img.add[i] = rt->color;
	rt->img.add[i + 1] = rt->color >> 8;
	rt->img.add[i + 2] = rt->color >> 16;
	return (0);
}
