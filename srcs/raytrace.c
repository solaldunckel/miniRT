/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 01:48:25 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	plane(t_mini_rt *rt, t_element *plane)
{
	rt->t = ((plane->point.x * (rt->cam->pov.x - plane->point.x)
			+ plane->point.y * (rt->cam->pov.y - plane->point.y)
			+ plane->point.z * (rt->cam->pov.z - plane->point.z) ) /
			(plane->point.x * rt->ray.dir.x
				+ plane->point.y * rt->ray.dir.y
				+ plane->point.z * rt->ray.dir.z));
}

int		interse(double a, double b, double det)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(det)) / (2 * a);
	t2 = (-b + sqrt(det)) / (2 * a);
	return (t1 < t2 ? t1 : t2);
}

void	cylinder(t_mini_rt *rt, t_element *cylinder)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;

	t = 0;
	a = pow(rt->ray.dir.x, 2) + pow(rt->ray.dir.y, 2);
	b = 2 * (rt->ray.dir.x * (rt->cam->pov.x - cylinder->point.x)
		+ rt->ray.dir.y * (rt->cam->pov.y - cylinder->point.y));
	c = (pow(rt->cam->pov.x - cylinder->point.x, 2)
		+ pow(rt->cam->pov.y - cylinder->point.y, 2)
		- pow(cylinder->diameter / 1.5, 2));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
	{
		rt->t = -1;
		return ;
	}
	rt->t = interse(a, b, det);
}


void	find_objs(t_mini_rt *rt, t_element *obj)
{
	ft_strequ(obj->id, SPHERE) ? sphere(rt, obj) : 0;
	//ft_strequ(obj->id, SQUARE) ? square(rt, obj) : 0;
	//ft_strequ(obj->id, PLANE) ? plane(rt, obj) : 0;
	//ft_strequ(obj->id, TRIANGLE) ? triangle(rt, obj) : 0;
	ft_strequ(obj->id, CYLINDER) ? cylinder(rt, obj) : 0;
}

void	ray_inter(t_mini_rt *rt, int x, int y)
{
	t_list		*tmp;

	rt->obj = NULL;
	rt->col = 0x000000;
	tmp = rt->elem_list;
	rt->k = 0;
	while (tmp)
	{
		find_objs(rt, tmp->content);
		if (rt->t >= 0 && rt->k <= rt->t)
		{
			rt->k = rt->t;
			rt->obj = tmp->content;
		}
		tmp = tmp->next;
	}
	if (rt->obj)
	{
		// on calcule la couleur sur l'obj enregistré avec lumiere + shadow
		rt->col = convert_rgb(rt->obj->color.r, rt->obj->color.g, rt->obj->color.b);
		color_put(rt, x, y);
	}
}

int		raytracing(t_mini_rt *rt)
{
	int		x;
	int		y;
	double 	angle;

	y = 0;
	rt->cam->fov = 70;
	rt->k = 0;
	angle = tan(M_PI * 0.5 * rt->cam->fov / 180);
	while (y < rt->res.y)
	{
		x = 0;
		while (x < rt->res.x)
		{
			rt->ray.dir.x = (2 * (x + 0.5) / rt->res.x) - 1 * angle;
			rt->ray.dir.y = (1 - 2 * (y + 0.5) / rt->res.y) * angle;
			rt->ray.dir.z = -1;
			ray_inter(rt, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
