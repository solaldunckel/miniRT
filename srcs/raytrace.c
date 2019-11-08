/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:24:40 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 17:59:16 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	ft_sphere(t_mini_rt *rt, t_element *sphere)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t1;
	double	t2;
	double	tf;

	a = pow(rt->x, 2) + pow(rt->y, 2) + pow(1, 2);
	b = 2 * (rt->x * (rt->cam->pov.x - sphere->point.x) + 1 * (rt->cam->pov.y - sphere->point.y) + 1 * (rt->cam->pov.z - sphere->point.z));
	c = (pow(rt->cam->pov.x - sphere->point.x, 2) + pow(rt->cam->pov.y - sphere->point.y, 2) + pow(rt->cam->pov.z - sphere->point.x, 2)) - pow(sphere->diameter / 2, 2);
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
		tf = 10001;
	if (det == 0)
		tf = -b / (2 * a);
	else if (det > 0)
	{
		t1 = (-b + sqrt(det)) / (2 * a);
		t2 = (-b - sqrt(det)) / (2 * a);
		t1 < t2 ? tf = t1 : 0;
		t1 > t2 ? tf = t2 : 0;
	}
	if (tf < rt->t)
	{
		rt->t = tf;
		rt->col = createRGB(sphere->color.r, sphere->color.g, sphere->color.b);
		rt->obj = (void *)sphere;
	}
	//printf("[%s][%f][%f]\n", sphere->id, det, tf);
}

void	ft_square(t_mini_rt *rt, t_element *square)
{
	(void)square;
	(void)rt;
	printf("%s\n", square->id);
}

void	ft_plane(t_mini_rt *rt, t_element *plane)
{
	(void)plane;
	(void)rt;
	printf("%s\n", plane->id);
}

void	ft_triangle(t_mini_rt *rt, t_element *triangle)
{
	(void)triangle;
	(void)rt;
	printf("%s\n", triangle->id);
}

void	ft_cylinder(t_mini_rt *rt, t_element *cylinder)
{
	(void)cylinder;
	(void)rt;
	printf("%s\n", cylinder->id);
}

void	ft_ray(t_mini_rt *rt)
{
	t_list		*temp;
	t_element 	*elem;

	temp = rt->list;
	while (temp)
	{
		elem = temp->content;
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
	rt->y = 0;
	while (rt->y < rt->res.y)
	{
		rt->x = 0;
		while (rt->x < rt->res.x)
		{
			rt->col = 0x000000;
			rt->t = 70;
			ft_ray(rt);
			color_put(rt);
			rt->x++;
		}
		rt->y++;
	}
	return (0);
}
