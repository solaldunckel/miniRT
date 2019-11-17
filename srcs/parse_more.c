/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:40:08 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/17 16:42:39 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_antialiasing(t_mini_rt *rt)
{
	if (check_split(rt->split) != 2)
		handle_error("invalid anti aliasing", rt);
	rt->anti_aliasing = ft_atoi(rt->split[1]);
	if (rt->anti_aliasing < 1)
		handle_error("anti aliasing too small", rt);
	return (1);
}
