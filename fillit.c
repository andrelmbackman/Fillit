/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:09 by abackman          #+#    #+#             */
/*   Updated: 2022/01/20 18:56:20 by abackman         ###   ########.fr       */
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

/*
** Takes the file descriptor (fd), the buffer (buf), buffer's index (i)
** and the number of bytes read (r_bytes). 
** Iterates through the buffer one piece at a time and checks
** if it's valid, if so it puts them in a list and assigns them
** a letter in the alphabetical order. 
*/

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

/*
** read_file function, attempts to read the whole file, up to 546 bytes,
** which would be required for maximum 26 tetrimino pieces including the
** '\n'. It checks that the file has no more than 26 pieces nor less than
** 1 piece assuming that the file is written correctly. 
*/

t_piece	*read_file(size_t r_bytes, char *buf, int fd)
{
	size_t	i;

	i = 0;
	r_bytes = read(fd, buf, 547);
	if (r_bytes > 546 || r_bytes < 19)
		error_exit(fd);
	buf[r_bytes] = '\0';
	return (make_piecelist(r_bytes, i, buf, fd));
}

void	error_exit()
{	
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	char		buf[546];
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
