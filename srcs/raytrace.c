/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 15:13:52 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int     color_put(t_mini_rt *rt)
{
    int i;

    i = rt->y * rt->img.size_line + rt->img.bpp / 8 * rt->x;
    if (i < 1)
        return (0);
    rt->img.add[i] = rt->col;
    rt->img.add[i + 1] = rt->col >> 8;
    rt->img.add[i + 2] = rt->col >> 16;
    return (0);
}

void	ft_sphere(t_mini_rt *rt, t_element *sphere)
{
	(void)sphere;
	(void)rt;
	printf("Yes frr\n");
}

void	ft_ray(t_mini_rt *rt)
{
	t_list		*temp;
	t_element 	*elem;

	temp = rt->list;
	while (temp)
	{
		elem = temp->content;
		ft_printf("test\n");
		ft_strequ(elem->id, "sphere") ? ft_sphere(rt, elem) : 0;
		//ft_strequ(elem->id, "square") ? ft_square(rt, elem) : 0;
		//ft_strequ(elem->id, "plane") ? ft_plane(rt, elem) : 0;
		//ft_strequ(elem->id, "triangle") ? ft_triangle(rt, elem) : 0;
		//ft_strequ(elem->id, "cylinder") ? ft_cylinder(rt, elem) : 0;
		temp = temp->next;
	}
}

int		raytracing(t_mini_rt *rt)
{
	while (rt->y < rt->res.y)
	{
		rt->x = 0;
		while (rt->x < rt->res.x)
		{
			ft_ray(rt);
			color_put(rt);
			rt->x++;
		}
		rt->y++;
	}
	return (0);
}
