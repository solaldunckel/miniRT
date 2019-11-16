/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:04:25 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/16 19:00:00 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			color_put(t_mini_rt *rt, int x, int y, int color)
{
	int i;

	i = y * rt->cam->img.size_line + rt->cam->img.bpp / 8 * x;
	if (i < 1)
		return (0);
	rt->cam->img.add[i] = color;
	rt->cam->img.add[i + 1] = color >> 8;
	rt->cam->img.add[i + 2] = color >> 16;
	return (0);
}

t_color		color_average(t_color color1, t_color color2)
{
	t_color		color;

	color.r = (color1.r + color2.r) / 2;
	color.g = (color1.g + color2.g) / 2;
	color.b = (color1.b + color2.b) / 2;
	return (color);
}

t_color		color_add(t_color color1, t_color color2)
{
	t_color		color;

	color.r = color1.r + color2.r;
	color.g = color1.g + color2.g;
	color.b = color1.b + color2.b;
	return (color);
}

t_color		color_div(t_color color, int average)
{
	t_color		c;

	c.r = color.r / average;
	c.g = color.g / average;
	c.b = color.b / average;
	return (c);
}
