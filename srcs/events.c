/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:42:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 16:08:27 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
	if (key == 53)
		exit_and_free(rt);
	return (0);
}

int		get_cross_button(t_mini_rt *rt)
{
	(void)rt;
	exit_and_free(rt);
	return (0);
}

int		handle_error(char *str, t_mini_rt *rt)
{
	ft_printf("" RED "miniRT Error: %s\n" RESET, str);
	ft_lstclear(&rt->list, free_element);
	exit(0);
	return (0);
}

int		exit_and_free(t_mini_rt *rt)
{
	ft_printf("" BOLDGREEN "Exiting miniRT...\n" RESET);
	ft_lstclear(&rt->list, free_element);
	exit(1);
	return (0);
}
