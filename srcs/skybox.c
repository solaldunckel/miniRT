/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haguerni <haguerni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:48:28 by haguerni          #+#    #+#             */
/*   Updated: 2019/11/30 21:49:49 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_texture	create_sky(t_mini_rt *rt, char *file_path)
{
	t_texture tex;

	if (!(tex.ptr = mlx_xpm_file_to_image(rt->mlx_ptr, file_path,
		&tex.width, &tex.height)))
		handle_error("fail creating skybox", rt);
	if (!(tex.img = mlx_get_data_addr(tex.ptr, &tex.bpp,
		&tex.size_line, &tex.endian)))
		handle_error("fail creating skybox", rt);
	return (tex);
}

t_color		get_sky_color(t_texture sky, float x, float y, float max)
{
	int		i;
	int		column;
	int		row;
	t_color	color;

	max = fabs(max);
	column = (int)(sky.width * (0.5 * (x / max + 1)));
	row = (int)(sky.height * (0.5 * (y / max + 1)));
	i = row * sky.size_line + sky.bpp / 8 * column;
	color.b = (float)(unsigned char)sky.img[i] / 255;
	color.g = (float)(unsigned char)sky.img[i + 1] / 255;
	color.r = (float)(unsigned char)sky.img[i + 2] / 255;
	return (color);
}

void		free_sky(t_mini_rt *rt)
{
	int		i;

	i = 0;
	while (rt->sky[i].img)
	{
		if (rt->sky[i].img)
			mlx_destroy_image(rt->mlx_ptr, rt->sky[i].ptr);
		i++;
	}
	free(rt->sky);
}

t_color		get_sky_coord(t_mini_rt *rt)
{
	t_color	color;
	float	m;

	ft_bzero(&color, sizeof(t_color));
	rt->ray.dir = vec_normalize(rt->ray.dir);
	if (fabs(rt->ray.dir.z) >= fabs(rt->ray.dir.y) && fabs(rt->ray.dir.z)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.z <= 0 && (m = rt->ray.dir.z) >= 0)
		color = get_sky_color(rt->sky[0], -rt->ray.dir.x, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.z) >= fabs(rt->ray.dir.y) && fabs(rt->ray.dir.z)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.z >= 0 && (m = rt->ray.dir.z) >= 0)
		color = get_sky_color(rt->sky[1], rt->ray.dir.x, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.x) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.x)
	>= fabs(rt->ray.dir.y) && rt->ray.dir.x <= 0 && (m = rt->ray.dir.x) >= 0)
		color = get_sky_color(rt->sky[2], rt->ray.dir.z, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.x) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.x)
	>= fabs(rt->ray.dir.y) && rt->ray.dir.x >= 0 && (m = rt->ray.dir.x) >= 0)
		color = get_sky_color(rt->sky[3], -rt->ray.dir.z, -rt->ray.dir.y, m);
	else if (fabs(rt->ray.dir.y) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.y)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.y <= 0 && (m = rt->ray.dir.y) >= 0)
		color = get_sky_color(rt->sky[4], rt->ray.dir.x, -rt->ray.dir.z, m);
	else if (fabs(rt->ray.dir.y) >= fabs(rt->ray.dir.z) && fabs(rt->ray.dir.y)
	>= fabs(rt->ray.dir.x) && rt->ray.dir.y >= 0 && (m = rt->ray.dir.y) >= 0)
		color = get_sky_color(rt->sky[5], rt->ray.dir.x, rt->ray.dir.z, m);
	return (color);
}
