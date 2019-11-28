/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:56:12 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/28 16:07:36 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			check_orient(t_vec *orient)
{
	if (orient->x > 1)
		orient->x = 1;
	else if (orient->x < -1)
		orient->x = -1;
	else if (orient->y > 1)
		orient->y = 1;
	else if (orient->y < -1)
		orient->y = -1;
	else if (orient->z > 1)
		orient->z = 1;
	else if (orient->z < -1)
		orient->z = -1;
	else
		return (1);
	return (0);
}

void		show_keybind(t_mini_rt *rt)
{
	if (rt->kb)
	{
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 5, 0xFFFFFF,
			"Switch Camera : TAB");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 25, 0xFFFFFF,
			"Move Camera : W,A,S,D,Q,E");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 45, 0xFFFFFF,
			"Orient Camera : T,F,G,H,R,Y");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 65, 0xFFFFFF,
			"Select Object : ENTER");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 85, 0xFFFFFF,
			"Unselect Object : \\");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 105, 0xFFFFFF,
			"Move Object : UP,LEFT,DOWN,RIGHT,N,M");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 125, 0xFFFFFF,
			"Orient Object : I,J,K,L,U,O");
	}
	else
		mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->cam->img.ptr,
			0, 0);
}

void		redraw_window(t_mini_rt *rt)
{
	int		i;

	i = 0;
	while (i < rt->cam->img.size_line * rt->res.y)
	{
		rt->cam->img.add[i] = 0;
		i++;
	}
	setup_rt(rt);
	multi_thread(rt);
	mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->cam->img.ptr, 0, 0);
	show_keybind(rt);
}

t_element	*element_cpy(t_element *elem)
{
	t_element	*new_elem;

	if (!(new_elem = ft_calloc(1, sizeof(t_element))))
		return (NULL);
	ft_memcpy(new_elem, elem, sizeof(t_element));
	return (new_elem);
}
