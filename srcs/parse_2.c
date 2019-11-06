/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:56 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/02 18:22:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_sphere(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("sphere\n");
	return (1);
}

int		parse_plane(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("plane\n");
	return (1);
}

int		parse_square(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("square\n");
	return (1);
}

int		parse_cylindre(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("cylindre\n");
	return (1);
}

int		parse_triangle(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("triangle\n");
	return (1);
}
