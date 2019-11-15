/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:42:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/15 17:19:15 by haguerni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		handle_error(char *str, t_mini_rt *rt)
{
	ft_printf("" RED "Error\n>> %s <<\n" RESET, str);
	if (rt->split)
		free_split(rt->split);
	if (rt->line)
		ft_strdel(&rt->line);
	ft_lstclear(&rt->objs_list, free_element);
	ft_lstclear(&rt->cam_list, free_element);
	ft_lstclear(&rt->light_list, free_element);
	exit(1);
	return (0);
}

int		exit_and_free(t_mini_rt *rt)
{
	ft_printf("" BOLDGREEN "Exiting miniRT...\n" RESET);
	ft_lstclear(&rt->objs_list, free_element);
	ft_lstclear(&rt->cam_list, free_element);
	ft_lstclear(&rt->light_list, free_element);
	if (!rt->save)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	}
	mlx_destroy_image(rt->mlx_ptr, rt->img.ptr);
	exit(0);
	return (0);
}

void	free_element(void *elem)
{
	t_element	*tmp;

	tmp = elem;
	free(tmp);
}

int		get_keypress(int key, t_mini_rt *rt)
{
	(void)rt;
	if (key == 17)
		change_cam(rt);
	if (key == 53)
		exit_and_free(rt);
	return (0);
}
