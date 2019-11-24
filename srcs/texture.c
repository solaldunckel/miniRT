/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:39:46 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/24 04:49:52 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	create_texture(t_mini_rt *rt, t_element *elem, char *file_path)
{
	if (!(elem->tex.ptr = mlx_xpm_file_to_image(rt->mlx_ptr, file_path,
		&elem->tex.width, &elem->tex.height)))
		handle_error("fail creating texture", rt);
	if (!(elem->tex.img = mlx_get_data_addr(elem->tex.ptr, &elem->tex.bpp,
		&elem->tex.size_line, &elem->tex.endian)))
		handle_error("fail creating texture", rt);
}

t_color	get_color(t_mini_rt *rt)
{
	int		i;
	int		column;
	int		row;
	t_color	color;

	i = 0;
	column = 0;
	row = 0;
	if (rt->obj->id == SPHERE && rt->obj->tex.ptr)
	{
		get_tex_coord(rt, rt->obj, &column, &row);
		i = row * rt->obj->tex.size_line + rt->obj->tex.bpp / 8 * column;
		color.b = abs(rt->obj->tex.img[i]);
		color.g = abs(rt->obj->tex.img[i + 1]);
		color.r = abs(rt->obj->tex.img[i + 2]);
	}
	else
	{
		color.r = rt->obj->color.r;
		color.g = rt->obj->color.g;
		color.b = rt->obj->color.b;
	}
	return (color);
}

void	get_tex_coord(t_mini_rt *rt, t_element *sphere, int *column, int *row)
{
	float	u;
	float	v;
	t_vec	n;
	t_vec	p;

	p = vec_add(rt->ray.ori, vec_mul(rt->ray.dir, rt->k));
	n = vec_normalize(vec_sub(p, sphere->point));
	u = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	*column = (int)(sphere->tex.width * u);
	*row = (int)(sphere->tex.height * v);
}
