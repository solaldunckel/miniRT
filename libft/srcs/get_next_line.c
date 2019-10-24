/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 22:14:46 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/24 22:24:58 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen_gnl(char *s)
{
	size_t		i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int		handle_line(char *s[], char **line, int fd)
{
	*line = ft_substr(s[fd], 0, ft_strlen_gnl(s[fd]));
	if (ft_is_in_stri('\n', s[fd]) >= 0)
		s[fd] = ft_substr(s[fd], ft_is_in_stri('\n', s[fd]) + 1, ft_strlen(s[fd]));
	else if (ft_strlen_gnl(s[fd]) > 0)
		s[fd] = ft_substr(s[fd], 0, ft_strlen(s[fd]));
	else
		return (FINISH);
	return (SUCCESS);
}

int				get_next_line(int fd, char **line)
{
	static char		*s[1024];
	char			buf[BUFFER_SIZE + 1];
	int				ret;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (ERROR);
	if (!s[fd] && !(s[fd] = malloc(sizeof(char *))))
		return (ERROR);
	while ((ft_is_in_stri('\n', s[fd])) < 0
		&& (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = s[fd];
		s[fd] = ft_strjoin(s[fd], buf);
		free(tmp);
	}
	if (!handle_line(s, &*line, fd))
		return (FINISH);
	return (SUCCESS);
}
