/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:09 by abackman          #+#    #+#             */
/*   Updated: 2022/01/19 13:28:12 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_piece	*free_tetri(t_piece *tetri)
{
	t_piece	*tmp;

	while (tetri)
	{
		tmp = tetri;
		tetri = tetri->next;
		free(tmp);
	}
	return (NULL);
}

t_piece	*make_piecelist(size_t r_bytes, size_t i, char *buf, int fd)
{
	t_piece	*head;
	t_piece	*next;
	char	letter;

	letter = 'A';
	while (i <= r_bytes)
	{
		if (letter == 'A')
		{
			head = check_tetri(buf, letter, fd);
			next = head;
		}
		else
		{
			next->next = check_tetri(buf + i, letter, fd);
			next = next->next;
		}
		letter++;
		i += 21;
		if (!head && !next)
			return (free_tetri(head));
	}
	next->next = NULL;
	head->last_letter = next->letter;
	return (head);
}

t_piece	*read_file(size_t r_bytes, char *buf, int fd)
{
	size_t	i;
	char	letter;

	i = 0;
	letter = 'A';	
	r_bytes = read(fd, buf, 545);
	if (r_bytes > 544 || r_bytes < 19)
		error_exit(fd);
	buf[r_bytes] = '\0';
	return (make_piecelist(r_bytes, i, buf, fd));
}

void	error_exit(int fd)
{
	close(fd);
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	char		buf[545];
	int			fd;
	size_t		r_bytes;
	t_piece		*tetris;

	r_bytes = 0;
	tetris = NULL;
	if (argc != 2)
		ft_putstr("usage: ./fillit source_file\n");
	else
	{	
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			error_exit(fd);
		tetris = read_file(r_bytes, buf, fd);
		if (tetris)
			solve_map(tetris);
		else
			error_exit(fd);
		close(fd);
	}
	return (0);
}
