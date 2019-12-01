/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:04:25 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/01 22:11:10 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		apply_sepia(t_mini_rt *rt)
{
	float		red;
	float		green;
	float		blue;

	red = 0.393 * rt->color.r + 0.769 * rt->color.g + 0.189 * rt->color.b;
	green = 0.349 * rt->color.r + 0.686 * rt->color.g + 0.168 * rt->color.b;
	blue = 0.272 * rt->color.r + 0.534 * rt->color.g + 0.131 * rt->color.b;
	if (red > 1)
		rt->color.r = 1;
	else
		rt->color.r = red;
	if (green > 1)
		rt->color.g = 1;
	else
		rt->color.g = green;
	if (blue > 1)
		rt->color.b = 1;
	else
		rt->color.b = blue;
}

int			color_put(t_mini_rt *rt, int x, int y)
{
	int		i;
	int		column;
	int		row;

	i = y * rt->cam->img.size_line + rt->cam->img.bpp / 8 * x;
	column = 0;
	row = 0;
	rt->st && rt->tr % 2 == 0 ? rt->color.r = 0 : 0;
	rt->st && rt->tr % 2 == 1 ? rt->color.g = 0 : 0;
	if (i < 1)
		return (0);
	rt->color.b *= 255;
	rt->color.g *= 255;
	rt->color.r *= 255;
	rt->cam->img.add[i] = rt->color.b;
	rt->cam->img.add[i + 1] = rt->color.g;
	rt->cam->img.add[i + 2] = rt->color.r;
	return (0);
}

t_color		color_average(t_color color1, t_color color2)
{
	t_color		color;

	color.r = color1.r * color2.r;
	color.g = color1.g * color2.g;
	color.b = color1.b * color2.b;
	return (color);
}

t_color		color_add(t_color color1, t_color color2, int cap)
{
	t_color		color;

	color.r = color1.r + color2.r;
	color.r > 1 && cap ? color.r = 1 : 0;
	color.g = color1.g + color2.g;
	color.g > 1 && cap ? color.g = 1 : 0;
	color.b = color1.b + color2.b;
	color.b > 1 && cap ? color.b = 1 : 0;
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
