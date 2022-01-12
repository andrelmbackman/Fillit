/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:09 by abackman          #+#    #+#             */
/*   Updated: 2022/01/12 16:11:56 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	ft_putstr(const char *s)
{
	int				i;
	unsigned char	ch;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		ch = (unsigned char)s[i];
		write(1, &ch, 1);
		i++;
	}
}

t_tetrimino *check_tetri(char *buf, size_t r_bytes)
{
	int	blocks;
	int	links;
	int	i;

	blocks = 0;
	links = 0;
	i = 0;
	while (i < 20)
	{
		if (buf[i] != '.' && buf[i] != '#' && buf[i] != '\n')
			ft_putstr("error1\n");
		if (buf[i] == '\n' && (i % 5) != 4)
			printf("error2 %d\n", i);
		if (buf[i] == '#')
		{
			blocks++;
			if (buf[i + 1] == '#' && (i + 1) < 20)
				links++;
			if (buf[i + 5] == '#' && (i + 5) < 20)
				links++;
		}
		i++;
	}
	printf("blocks: %i\nlinks: %i\nindex: %i\n", blocks, links, i);
	return (NULL);
}

t_tetrimino	*read_file(int fd)
{
	char		buf[21];
	t_tetrimino	*head;
	t_tetrimino	*tmp;
	size_t		r_bytes;

	r_bytes = read(fd, buf, 21);
	while (r_bytes > 0)
	{
		if (r_bytes < 19)
			return (NULL);
		tmp = check_tetri(buf, r_bytes);
		r_bytes = read(fd, buf, 21);
	}
/*	if (tmp)
		tmp = add_tetri(head, tmp);
	else
	{
		ft_putstr("error\n");
		ft_lstdel(head);
	}
	*/
	return (head);
}
/*
void	solve_map(t_tetrimino *tetris)
{

}
*/
int	main(int argc, char **argv)
{
	int			fd;
	t_tetrimino	*tetris;

	if (argc != 2)
		ft_putstr("usage: ./fillit tetrimino_file\n");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			ft_putstr("error\n");
		else
			tetris = read_file(fd);
		//if (tetris)
		//	solve_map(tetris);
		//else
		//	ft_putstr("error\n");
	}
	close(fd);
	return (0);
}
