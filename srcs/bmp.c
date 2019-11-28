/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:41:20 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/28 13:28:37 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	bitmap_file_header(t_mini_rt *rt, int padding_size, int fd)
{
	unsigned char	*file_header;
	int				file_size;

	if (!(file_header = ft_calloc(BMP_FILE_HEADER_SIZE, sizeof(unsigned char))))
		handle_error("fail to malloc", rt);
	file_size = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE
		+ (rt->cam->img.bpp / 8 * rt->res.x + padding_size) * rt->res.y;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(BMP_FILE_HEADER_SIZE
		+ BMP_INFO_HEADER_SIZE);
	write(fd, file_header, BMP_FILE_HEADER_SIZE);
	file_header = NULL;
	free(file_header);
}

void	bitmap_info_header(t_mini_rt *rt, int fd)
{
	unsigned char	*info_header;

	if (!(info_header = ft_calloc(BMP_INFO_HEADER_SIZE, sizeof(unsigned char))))
		handle_error("fail to malloc", rt);
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(rt->res.x);
	info_header[5] = (unsigned char)(rt->res.x >> 8);
	info_header[6] = (unsigned char)(rt->res.x >> 16);
	info_header[7] = (unsigned char)(rt->res.x >> 24);
	info_header[8] = (unsigned char)(rt->res.y);
	info_header[9] = (unsigned char)(rt->res.y >> 8);
	info_header[10] = (unsigned char)(rt->res.y >> 16);
	info_header[11] = (unsigned char)(rt->res.y >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(rt->cam->img.bpp);
	write(fd, info_header, BMP_INFO_HEADER_SIZE);
	info_header = NULL;
	free(info_header);
}

void	create_bmp_image(t_mini_rt *rt, char *file_name)
{
	int				i;
	int				fd;
	int				padding_size;
	unsigned char	padding[3];

	i = rt->res.y;
	ft_bzero(padding, 3);
	if (!(fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		handle_error("fail to export bmp file", rt);
	padding_size = (4 - (rt->res.x * rt->img.bpp / 8) % 4) % 4;
	bitmap_file_header(rt, padding_size, fd);
	bitmap_info_header(rt, fd);
	while (i >= 0)
	{
		write(fd, rt->cam->img.add + (i * rt->res.x * rt->cam->img.bpp / 8),
				rt->cam->img.size_line);
		write(fd, padding, padding_size);
		i--;
	}
	close(fd);
}
