/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 00:24:57 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/12 12:35:23 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rx(t_vec *v, double x)
{
	t_vec	tmp;

	tmp.x = v->x;
	tmp.y = v->y * cos(x) - v->z * sin(x);
	tmp.z = v->y * sin(x) + v->z * cos(x);
	*v = tmp;
}

void	ry(t_vec *v, double y)
{
	t_vec	tmp;

	tmp.x = v->x * cos(y) + v->z * sin(y);
	tmp.y = v->y;
	tmp.z = v->x * -sin(y) + v->z * cos(y);
	*v = tmp;
}

void	rz(t_vec *v, double z)
{
	t_vec	tmp;

	tmp.x = v->x * cos(z) - v->y * sin(z);
	tmp.y = v->x * sin(z) + v->y * cos(z);
	tmp.z = v->z;
	*v = tmp;
}

void	rotate_vector(t_vec *v, t_vec *rot)
{
	rx(v, rot->x);
	ry(v, rot->y);
	rz(v, rot->z);
}

void	vec_normalize(t_vec *v)
{
    float	len;

	len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}
