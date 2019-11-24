/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:42:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/24 04:44:12 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_texture(t_mini_rt *rt)
{
	t_list		*tmp;
	t_element	*obj;

	tmp = rt->objs_list;
	while (tmp)
	{
		obj = tmp->content;
		if (obj->tex.img)
			mlx_destroy_image(rt->mlx_ptr, obj->tex.ptr);
		tmp = tmp->next;
	}
}

void	free_camera(t_mini_rt *rt)
{
	t_list		*tmp;
	t_camera	*cam;

	tmp = rt->cam_list;
	while (tmp)
	{
		cam = tmp->content;
		if (cam->img.ptr)
			mlx_destroy_image(rt->mlx_ptr, cam->img.ptr);
		tmp = tmp->next;
	}
}

void	handle_error(char *str, t_mini_rt *rt)
{
	ft_printf("" RED "Error\n>> %s <<\n" RESET, str);
	if (rt->split)
		free_split(rt->split);
	if (rt->line)
		ft_strdel(&rt->line);
	free_camera(rt);
	free_texture(rt);
	ft_lstclear(&rt->objs_list, free);
	ft_lstclear(&rt->cam_list, free);
	ft_lstclear(&rt->light_list, free);
	exit(EXIT_FAILURE);
}

int		exit_and_free(t_mini_rt *rt)
{
	ft_printf("" BOLDGREEN "Exiting miniRT...\n" RESET);
	free_camera(rt);
	//free_texture(rt);
	ft_lstclear(&rt->objs_list, free);
	ft_lstclear(&rt->cam_list, free);
	ft_lstclear(&rt->light_list, free);
	if (!rt->save)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	}
	exit(EXIT_SUCCESS);
	return (1);
}

int		get_keypress(int key, t_mini_rt *rt)
{
	if (key == KEY_TAB)
		change_cam(rt);
	else if (key == KEY_ESC)
		exit_and_free(rt);
	key_hook(key, rt);
	return (1);
}
