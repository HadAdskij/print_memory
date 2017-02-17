/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 11:36:03 by exam              #+#    #+#             */
/*   Updated: 2017/01/23 13:54:38 by atytaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

typedef unsigned char u_char;

void	print_memory(const void *addr, size_t size)
{
	char		str[16];
	size_t		i;
	int			j;
	char		*a;
	char		ch[2];

	a = (char*)addr;
	i = -1;
	while (++i < size)
	{
		ch[0] = (u_char)a[i] / 16 + ((u_char)a[i] / 16 > 9 ? 87 : 48);
		ch[1] = (u_char)a[i] % 16 + ((u_char)a[i] % 16 > 9 ? 87 : 48);
		write(1, ch, 2);
		if (i % 2 == 1)
			write(1, " ", 1);
		str[i % 16] = (a[i] >= ' ' && a[i] < 127) ? a[i] : '.' ;
		if (i % 16 == 15 || i == size - 1)
		{
			j = i;
			if (i == size - 1)
				while (i++ % 16 != 15)
					write(1, "   ", i % 2 + 2);
			write(1, str, j % 16 + 1);
			write(1, "\n", 1);
			j = -1;
		}
	}
}

int		main(int ac, char **av)
{
	int		fd;
	char	buf[160];
	size_t	sz;

	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
		{
			write(2, "error\n", 6);
			return (0);
		}
		while ((sz = read(fd, buf, 160)) > 0)
			print_memory(buf, sz);
		close(fd);
	}
	return (0);
}
