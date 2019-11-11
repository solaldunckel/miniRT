/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:00:00 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/11 11:33:09 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vec	vec_mul(t_vec v1, double m)
{
	t_vec	v;

	v.x = v1.x * m;
	v.y = v1.y * m;
	v.z = v1.z * m;
	return (v);
}

t_vec	vec_div(t_vec v1, double d)
{
	t_vec	v;

	v.x = v1.x / d;
	v.y = v1.y / d;
	v.z = v1.z / d;
	return (v);
}

t_vec	vec_dot(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}
