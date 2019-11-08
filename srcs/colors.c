/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:04:25 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/08 15:16:15 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int     color_put(t_mini_rt *rt)
{
    int i;

    i = rt->y * rt->img.size_line + rt->img.bpp / 8 * rt->x;
    if (i < 1)
        return (0);
    rt->img.add[i] = rt->col;
    rt->img.add[i + 1] = rt->col >> 8;
    rt->img.add[i + 2] = rt->col >> 16;
    return (0);
}
