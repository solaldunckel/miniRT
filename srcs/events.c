/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:42:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/10 23:28:05 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		exit_and_free(t_mini_rt *rt)
{
	ft_printf("" BOLDGREEN "Exiting miniRT...\n" RESET);
	ft_lstclear(&rt->elem_list, free_element);
	ft_lstclear(&rt->cam_list, free_element);
	ft_lstclear(&rt->light_list, free_element);
	if (!rt->save)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	}
	mlx_destroy_image(rt->mlx_ptr, rt->img.ptr);
	exit(1);
	return (0);
}

void	free_element(void *elem)
{
	t_element 	*tmp;

	tmp = elem;
	free(tmp->id);
	free(tmp);
}

int		get_keypress(int key, t_mini_rt *rt)
{
	(void)rt;
	if (key == 17)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		select_cam(rt);
		raytracing(rt);
		mlx_key_hook(rt->win_ptr, get_keypress, rt);
		mlx_hook(rt->win_ptr, 17, 0, exit_and_free, rt);
		mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img.ptr, 0, 0);
		mlx_loop(rt->mlx_ptr);
	}
	if (key == 53)
		exit_and_free(rt);
	return (0);
}

int		handle_error(char *str, t_mini_rt *rt)
{
	ft_printf("" RED "miniRT Error: %s\n" RESET, str);
	ft_lstclear(&rt->elem_list, free_element);
	ft_lstclear(&rt->cam_list, free_element);
	ft_lstclear(&rt->light_list, free_element);
	exit(0);
	return (0);
}
