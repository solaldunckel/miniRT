/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 02:02:23 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/08 16:07:13 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	build_bar(int percentage, int width)
{
	int	i;
	int ratio;

	i = 0;
	ratio = 100 / width;
	ft_putstr("\r[");
	while (i < width)
	{
		if (i < percentage / ratio)
			ft_putchar('.');
		else if (i == percentage / ratio)
			ft_putchar('.');
		else
			ft_putchar(' ');
		i++;
	}
	ft_putstr("] ");
	ft_printf("%d%%", percentage);
}

void	progress_bar(t_thread *thread)
{
	int	pos;
	int prec;
	int i;

	pos = 0;
	prec = 0;
	ft_putstr("" BOLDGREEN "");
	while (pos < 100)
	{
		i = -1;
		pos = 0;
		while (++i < THREAD_COUNT)
			pos += thread[i].scene.percent;
		pos /= THREAD_COUNT;
		if (pos > prec)
		{
			i = -1;
			build_bar(pos, 20);
			prec = pos;
		}
	}
	ft_putstr("" RESET "\n" "");
}
