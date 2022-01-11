/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:09 by abackman          #+#    #+#             */
/*   Updated: 2022/01/11 14:20:05 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetrimino	*read_file(int fd)
{
	char		buf[21];
	t_tetrimino	*head;
	t_tetrimino	*tmp;
	size_t		r_bytes;

	r_bytes = read(fd, buf, 21);
	while (r_bytes >= 20)
	{
		tmp = check_tetri(buf);
		if (!tmp)
			break ;
		else
			tmp = add_tetri(head, tmp);
		r_bytes = read(fd, buf, 21);
	}
	if (!tmp)
	{
		ft_putstr("error\n");
		ft_lstdel(head);
	}
	return (head);
}

void	solve_map(t_tetrimino *tetris)
{

}

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
		if (tetris)
			solve_map(tetris);
	}
	close(fd);
	return (0);
}
