/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:09 by abackman          #+#    #+#             */
/*   Updated: 2022/01/14 16:21:08 by abackman         ###   ########.fr       */
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

t_map	*fill_dots(t_map *map, int sqroot)
{
	int	i;

	i = 0;
	while (i < sqroot)
	{
		map->map[i] = ft_strnew(sqroot);
		ft_memset(map->map, '.', sqroot);
		i++;
	}
	return (map);
}

t_map	*create_map(t_piece *pieces)
{
	int		mapsize;
	int		sqroot;
	t_map	*map;

	mapsize = 4 * (pieces->last_letter - 'A');
	sqroot = 2;
	while (sqroot * sqroot < mapsize)
		sqroot++;
	map = (t_map *)malloc(sizeof (t_map));
	if (!map)
		return (NULL);
	map->map = (char **)malloc(sqroot * sizeof(char *));
	if (!map->map)
		return (NULL);
	else
		return (fill_dots(map, sqroot));
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

t_piece *make_piece(char *buf, char letter)
{
	t_piece		*tetri;
	int			i;
	int			x;
	int			y;

	i = 0;
	x = 0;
	y = 0;
	tetri = (t_piece *)malloc(sizeof(t_piece));
	if (tetri == NULL)
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
	printf(" %i %i %i %i %i %i %i %i\n", tetri->x_cord[0], tetri->y_cord[0], tetri->x_cord[1], tetri->y_cord[1], tetri->x_cord[2], tetri->y_cord[2], tetri->x_cord[3], tetri->y_cord[3]);
	shift_piece(tetri);
	tetri->letter = letter;
	printf(" %i %i %i %i %i %i %i %i\n", tetri->x_cord[0], tetri->y_cord[0], tetri->x_cord[1], tetri->y_cord[1], tetri->x_cord[2], tetri->y_cord[2], tetri->x_cord[3], tetri->y_cord[3]);
	printf("letter: %c\n", tetri->letter);
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

t_piece *check_tetri(char *buf, char letter)
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
			links = check_links(buf, i, links);
			printf("links: %i\n", links);
		}
		i++;
	}
	printf("blocks: %i\nlinks: %i\nindex: %i\n", blocks, links, i);
	if (blocks == 4 && (links == 3 || links == 4))
		return (make_piece(buf, letter));
	//else
	return (NULL);
}

t_piece	*read_file(size_t r_bytes, char *buf)
{
	t_piece		*head;
	t_piece		*next;
	int			i;
	char		letter;

	i = 0;
	letter = 'A';
	while (i <= r_bytes)
	{
		if (letter == 'A')
		{
			head = check_tetri(buf, letter);
			next = head;
		}
		else
		{
			next->next = check_tetri(buf + i, letter);
			next = next->next;
		}
		letter++;
		i += 21;
	}
	next->next = NULL;
	head->last_letter = next->letter;
	return (head);
}

int	main(int argc, char **argv)
{
	char		buf[545];
	int			fd;
	size_t		r_bytes;
	t_piece	*tetris;

	if (argc != 2)
		ft_putstr("usage: ./fillit source_file\n");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			ft_putstr("error\n");
		else
		{
			r_bytes = read(fd, buf, 545);
			if (r_bytes > 544 || r_bytes < 19)
				return (1);
			buf[r_bytes] = '\0';
			tetris = read_file(r_bytes, buf);
		}
		//if (tetris)
		//	solve_map(tetris);
		//else
		//	ft_putstr("error\n");
	}
	close(fd);
	return (0);
}
