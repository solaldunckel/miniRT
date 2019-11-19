/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/19 12:34:58 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	find_objs(t_mini_rt *rt, t_element *obj, t_vec ori, t_vec dir)
{
	if (obj->id == SPHERE)
		sphere(rt, obj, ori, dir);
	else if (obj->id == PLANE)
		plane(rt, obj, ori, dir);
	else if (obj->id == CYLINDER)
		cylinder(rt, obj, ori, dir);
	else if (obj->id == CIRCLE)
		circle(rt, obj, ori, dir);
	else if (obj->id == TRIANGLE)
		triangle(rt, obj, ori, dir);
	else if (obj->id == SQUARE)
	 	square(rt, obj, ori, dir);
}

t_color	ray_intersect(t_mini_rt *rt)
{
	t_list		*tmp;
	t_color		color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	rt->obj = NULL;
	rt->t = INT_MAX;
	rt->k = INT_MAX;
	tmp = rt->objs_list;
	while (tmp)
	{
		find_objs(rt, tmp->content, rt->ray.ori, rt->ray.dir);
		if (rt->t > 0 && rt->t < rt->k)
		{
			rt->k = rt->t;
			rt->obj = tmp->content;
		}
		tmp = tmp->next;
	}
	if (rt->obj != NULL)
		color = apply_lights(rt);
	return (color);
}

t_vec	calc_ray(t_mini_rt *rt, double x, double y)
{
	t_vec	image_point;
	t_vec	dir;
	double	norm_x;
	double	norm_y;

	norm_x = ((x / (double)rt->res.x) - 0.5);
	norm_y = ((y / (double)rt->res.y) - 0.5);
	rt->res.x < rt->res.y ? norm_x *= rt->aspect : 0;
	rt->res.x > rt->res.y ? norm_y /= rt->aspect : 0;
	image_point = vec_add(vec_add(vec_mul(rt->cam->right, norm_x),
		vec_mul(rt->cam->up, norm_y)), vec_add(rt->ray.ori, rt->cam->orient));
	dir = vec_normalize(vec_sub(image_point, rt->ray.ori));
	return (dir);
}

t_color	anti_aliasing(t_mini_rt *rt, double i, double j)
{
	t_color color;
	int		aa;
	double	aax;
	double	aay;

	aa = 0;
	aay =  -(rt->anti_aliasing - 1) / rt->anti_aliasing;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	while (aa < (pow(rt->anti_aliasing, 2)))
	{
		aax = -(rt->anti_aliasing - 1) / rt->anti_aliasing;
		while (aax <= (rt->anti_aliasing - 1) / rt->anti_aliasing)
		{
			rt->ray.dir = calc_ray(rt, i + aax, j + aay);
			rt->color = ray_intersect(rt);
			color = color_add(color, rt->color);
			aax += 1 / (rt->anti_aliasing - 1);
			aa++;
		}
		aay += 1 / ((double)rt->anti_aliasing - 1);
	}
	color = color_div(color, aa);
	return (color);
}

void	raytracing(t_mini_rt *rt)
{
	double	i;
	double	j;

	j = -1;
	while (++j < rt->res.y)
	{
		i = -1;
		while (++i < rt->res.x)
		{
			if (rt->anti_aliasing > 1)
				rt->color = anti_aliasing(rt, i, j);
			else
			{
				rt->ray.dir = calc_ray(rt, i, j);
				rt->color = ray_intersect(rt);
			}
			rt->sepia ? apply_sepia(rt) : 0;
			rt->obj ? color_put(rt, i, j) : 0;
		}
	}
}
