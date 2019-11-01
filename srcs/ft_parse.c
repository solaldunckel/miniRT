/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:25:30 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/01 16:11:22 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		parse_res(t_mini_rt *rt, char *line)
{
	printf("parsing resolution\n");
	rt->i++;
	rt->res.x = ft_atoi(&line[rt->i]);
	rt->i += ft_intlen(rt->res.x) + 1;
	rt->res.y = ft_atoi(&line[rt->i]);
	return (1);
}

int		parse_ambient(t_mini_rt *rt, char *line)
{
	printf("\n\n");
	(void)rt;
	(void)line;
	//printf("parsing ambient\n");
	double	fl;
	char	str[] = "  203.987654321";
	fl = ft_atof(str);
	printf("float test : %.16f\n", fl);
	printf("\n\n");
	return (1);
}

int		parse_camera(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("parsing camera\n");
	return (1);
}

int		parse_light(t_mini_rt *rt, char *line)
{
	(void)line;
	(void)rt;
	printf("parsing light\n");
	return (1);
}
