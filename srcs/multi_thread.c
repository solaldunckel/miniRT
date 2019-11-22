/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:19:10 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/22 16:31:30 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


t_element	*element_cpy(t_element *elem)
{
	t_element	*new_elem;

	if (!(new_elem = ft_calloc(1, sizeof(t_element))))
		return (NULL);
	ft_memcpy(new_elem, elem, sizeof(t_element));
	return (new_elem);
}


void		ft_struct_dup(t_thread *th, t_mini_rt *rt)
{
	th->scene.objs_list = ft_lstmap(rt->objs_list, (void*)element_cpy, free);
	th->scene.cam_list = ft_lstmap(rt->cam_list, (void*)element_cpy, free);
	th->scene.light_list = ft_lstmap(rt->light_list, (void*)element_cpy, free);
}

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
		//ft_struct_dup(&thread[i], rt);
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
