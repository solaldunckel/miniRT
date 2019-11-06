/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:12:17 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/06 18:25:21 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_light		*new_light(t_mini_rt *rt)
{
	t_light		*lst;

	if (!(lst = ft_calloc(1, sizeof(t_light))))
		return (NULL);
	lst->point.x = ft_atof_rt(rt->line, rt);
	lst->point.y = ft_atof_rt(rt->line, rt);
	lst->point.z = ft_atof_rt(rt->line, rt);
	lst->ratio = ft_atof_rt(rt->line, rt);
	lst->color.r = ft_atoi_rt(rt->line, rt);
	lst->color.g = ft_atoi_rt(rt->line, rt);
	lst->color.b = ft_atoi_rt(rt->line, rt);
	lst->next = NULL;
	return (lst);
}

void	addback_light(t_light **begin, t_light *new)
{
	t_light	*tmp;

	if (!begin || !new)
		return ;
	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*begin = new;
}

void	free_light(t_light **lst)
{
	t_light	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		free(tmp);
		tmp = tmp->next;
	}
	*lst = NULL;
}

int		parse_light(t_mini_rt *rt)
{
	t_light		*light;

	light = new_light(rt);
	addback_light(&rt->light, light);
	if (DEBUG_PARSING)
		printf("light		point : %.f,%.f,%.f 	ratio : %.1f 		rgb : %d,%d,%d\n",
		light->point.x, light->point.y, light->point.z, light->ratio,
		light->color.r, light->color.g, light->color.b);
	return (1);
}
