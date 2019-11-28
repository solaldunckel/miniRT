/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 00:24:57 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/28 13:27:56 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vec	vec_abs(t_vec v1)
{
	t_vec	v;

	v.x = fabs(v1.x);
	v.y = fabs(v1.y);
	v.z = fabs(v1.z);
	return (v);
}

t_vec	vec_normalize(t_vec v)
{
	t_vec	norm;
	float	len;

	len = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

float	vec_len(t_vec v)
{
	float	len;

	len = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (len);
}
