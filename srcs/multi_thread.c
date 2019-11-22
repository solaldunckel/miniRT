/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:19:10 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 17:36:17 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		multi_thread(t_mini_rt *rt)
{
	int			i;
	pthread_t	thr[THREAD_COUNT];
	t_thread	thread[THREAD_COUNT];

	i = 0;
	while (i < THREAD_COUNT)
	{
		thread[i].cur_thr = i;
		ft_memcpy(&thread[i].scene, rt, sizeof(t_mini_rt));
		pthread_create(&thr[i], NULL, (void*)raytracing, &thread[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(thr[i], NULL);
		i++;
	}
}
