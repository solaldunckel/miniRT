/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:51:35 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/02 16:28:09 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	/*
	** GET_NEXT_LINE_TEST
	*/

	// int		fd;
	// char 	*line;
	// int		ret;
	//
	// fd = open(av[1], O_RDONLY);
	// while ((ret = get_next_line(fd, &line)))
	// {
	// 	printf("r : %d %s\n", ret, line);
	// }
	// return (0);

	/*
	** FT_PRINTF TEST
	*/

	int		ret1;
	int		ret2;

	ret1 = 0;
	ret2 = 0;

	ret1 = printf("on test tout %s\n", "les cas");
	ret2 = ft_printf("on test tout %s\n", "les cas");
	if (ret1 == ret2)
		printf("return OK");
	else
		printf("bad return");
}
