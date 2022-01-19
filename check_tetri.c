/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tetri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:58:27 by abackman          #+#    #+#             */
/*   Updated: 2022/01/19 13:32:05 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	shift_piece(t_piece *piece)
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

static t_piece	*make_piece(char *buf, char letter)
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

static int	check_links(char *buf, int i, int links)
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
