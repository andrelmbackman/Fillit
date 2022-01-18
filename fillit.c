/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:09 by abackman          #+#    #+#             */
/*   Updated: 2022/01/18 18:19:08 by abackman         ###   ########.fr       */
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

static void	fill_dots(t_map *map, int sqroot)
{
	int	i;

	i = 0;
	while (i < sqroot)
	{
		map->map[i] = ft_strnew(sqroot);
		ft_memset(map->map[i], '.', sqroot);
		i++;
	}
}

int	count_mapsize(t_piece *pieces)
{
	int		mapsize;
	int		sqroot;

	mapsize = 4 * (pieces->last_letter - 64);
	sqroot = 2;
	while (sqroot * sqroot < mapsize)
		sqroot++;
	return (sqroot);
}

t_map	*create_map(int sqroot)
{
	t_map	*map;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->size = sqroot;
	map->map = (char **)ft_memalloc(sqroot * sizeof(char *));
	fill_dots(map, sqroot);
	return (map);
}

void	shift_piece(t_piece *piece)
{
	while (piece->x_cord[0] != 0 && piece->x_cord[1] != 0 && \
	piece->x_cord[2] != 0 && piece->x_cord[3] != 0)
	{
		piece->x_cord[0] -= 1;
		piece->x_cord[1] -= 1;
		piece->x_cord[2] -= 1;
		piece->x_cord[3] -= 1;
	}
	while (piece->y_cord[0] != 0 && piece->y_cord[1] != 0 && \
	piece->y_cord[2] != 0 && piece->y_cord[3] != 0)
	{
		piece->y_cord[0] -= 1;
		piece->y_cord[1] -= 1;
		piece->y_cord[2] -= 1;
		piece->y_cord[3] -= 1;
	}
}

t_piece	*make_piece(char *buf, char letter)
{
	t_piece		*tetri;
	int			i;
	int			x;
	int			y;

	i = 0;
	x = 0;
	y = 0;
	tetri = (t_piece *)malloc(sizeof(t_piece));
	if (!tetri)
		return (NULL);
	while (i < 20)
	{
		if (buf[i] == '#')
		{
			if (i >= 5)
				tetri->x_cord[x++] = i % 5;
			else
				tetri->x_cord[x++] = i;
			tetri->y_cord[y++] = i / 5;
		}
		i++;
	}
	shift_piece(tetri);
	tetri->letter = letter;
	return (tetri);
}

int	check_links(char *buf, int i, int links)
{
	if (buf[i + 1] == '#' && (i + 1) < 20)
		links++;
	if (buf[i + 5] == '#' && (i + 5) < 20)
		links++;
	return (links);
}

t_piece	*check_tetri(char *buf, char letter, int fd)
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
			error_exit(fd);
		if (buf[i] == '\n' && (i % 5) != 4)
			error_exit(fd);
		if (buf[i] == '#')
		{
			blocks++;
			links = check_links(buf, i, links);
		}
		i++;
	}
	if (blocks == 4 && (links == 3 || links == 4))
		return (make_piece(buf, letter));
	else
		error_exit(fd);
	return (NULL);
}

t_piece	*read_file(size_t r_bytes, char *buf, int fd)
{
	t_piece		*head;
	t_piece		*next;
	size_t		i;
	char		letter;

	i = 0;
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

	tetris = NULL;
	if (argc != 2)
		ft_putstr("usage: ./fillit source_file\n");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			error_exit(fd);
		else
		{
			r_bytes = read(fd, buf, 545);
			if (r_bytes > 544 || r_bytes < 19)
				error_exit(fd);
			buf[r_bytes] = '\0';
			tetris = read_file(r_bytes, buf, fd);
		}
		if (tetris)
			solve_map(tetris);
		else
			error_exit(fd);
		close(fd);
	}
	return (0);
}
