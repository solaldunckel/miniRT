/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:04:25 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/17 16:18:27 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void 	apply_sepia(t_mini_rt *rt)
{
	double		red;
	double		green;
	double		blue;

	red = 0.393 * rt->color.r + 0.769 * rt->color.g + 0.189 * rt->color.b;
	green = 0.349 * rt->color.r + 0.686 * rt->color.g + 0.168 * rt->color.b;
	blue = 0.272 * rt->color.r + 0.534 * rt->color.g + 0.131 * rt->color.b;

	if (red > 255)
		rt->color.r = 255;
	else
		rt->color.r = (int)red;
	if (green > 255)
		rt->color.g = 255;
	else
		rt->color.g = (int)green;
	if (blue > 255)
		rt->color.b = 255;
	else
		rt->color.b = (int)blue;
}

int			color_put(t_mini_rt *rt, int x, int y)
{
	int i;

	i = y * rt->cam->img.size_line + rt->cam->img.bpp / 8 * x;
	if (i < 1)
		return (0);
	rt->cam->img.add[i] = rt->color.b;
	rt->cam->img.add[i + 1] = rt->color.g;
	rt->cam->img.add[i + 2] = rt->color.r;
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
