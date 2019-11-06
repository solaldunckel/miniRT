/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:42:50 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 15:26:23 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		get_keypress(int key, t_mini_rt *rt)
{
	(void)rt;
	if (key == 53)
	{
		ft_printf("" BOLDGREEN "Exiting miniRT...\n" RESET);
		exit(0);
	}
	return (0);
}

int		get_cross_button(t_mini_rt *rt)
{
	(void)rt;
	ft_printf("" BOLDGREEN "Exiting miniRT...\n" RESET);
	exit(0);
	return (0);
}
