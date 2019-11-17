/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:42:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/17 17:10:23 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		check_extension(t_mini_rt *rt, char *rt_file)
{
	int		i;

	i = ft_strlen(rt_file) - 1;
	if (rt_file[i] != 't' || rt_file[i - 1] != 'r' || rt_file[i - 2] != '.')
		handle_error("wrong file extension", rt);
}

void	free_camera(t_mini_rt *rt)
{
	t_list		*tmp;
	t_camera	*cam;

	tmp = rt->cam_list;
	while (tmp)
	{
		cam = tmp->content;
		mlx_destroy_image(rt->mlx_ptr, cam->img.ptr);
		tmp = tmp->next;
	}
}

int		handle_error(char *str, t_mini_rt *rt)
{
	ft_printf("" RED "Error\n>> %s <<\n" RESET, str);
	if (rt->split)
		free_split(rt->split);
	if (rt->line)
		ft_strdel(&rt->line);
	free_camera(rt);
	ft_lstclear(&rt->objs_list, free);
	ft_lstclear(&rt->cam_list, free);
	ft_lstclear(&rt->light_list, free);
	exit(1);
	return (0);
}

int		exit_and_free(t_mini_rt *rt)
{
	ft_printf("" BOLDGREEN "Exiting miniRT...\n" RESET);
	free_camera(rt);
	ft_lstclear(&rt->objs_list, free);
	ft_lstclear(&rt->cam_list, free);
	ft_lstclear(&rt->light_list, free);
	if (!rt->save)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	}
	exit(0);
	return (0);
}

int		get_keypress(int key, t_mini_rt *rt)
{
	if (key == 17)
		change_cam(rt);
	if (key == 53)
		exit_and_free(rt);
	return (0);
}
