/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tetri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:58:27 by abackman          #+#    #+#             */
/*   Updated: 2022/01/20 18:57:03 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Changes the coordinates of a valid tetrimino to the top-left corner.
** All the indexes of x_cord are decreased until at least one is 0.
** The same is done with y_cord.
*/

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

/*
** The make_piece function converts the character string representation
** of a tetrimino to 4 different x- and y-coordinates (x_cord[0-3] & 
** y_cord[0-3]). It then calls the shift_piece function to move the 
** coordinates to the top-left position. The letter is then stored
** in the t_piece structure.
*/

static t_piece	*make_piece(char *buf, char letter)
{
	t_piece		*tetri;
	int			i;
	int			x;
	int			y;

	i = -1;
	x = 0;
	y = 0;
	tetri = (t_piece *)malloc(sizeof(t_piece));
	if (!tetri)
		return (NULL);
	while (i++ < 20)
	{
		if (buf[i] == '#')
		{
			if (i >= 5)
				tetri->x_cord[x++] = i % 5;
			else
				tetri->x_cord[x++] = i;
			tetri->y_cord[y++] = i / 5;
		}
	}
	shift_piece(tetri);
	tetri->letter = letter;
	return (tetri);
}

/*
** This function checks whether there is a block
** character ('#') next to or under the given index.
** A valid tetrimino consists of 4 block characters
** and 3-4 links.
*/

static int	check_links(char *buf, int i, int links)
{
	if (buf[i + 1] == '#' && (i + 1) < 20)
		links++;
	if (buf[i + 5] == '#' && (i + 5) < 20)
		links++;
	return (links);
}

/*
** check_tetri checks if the character string (buf) is describing
** a valid tetrimino. A valid tetrimino should only contain 4 lines
** of 4 characters (and '\n'), the characters should be 4 blocks ('#')
** and the rest should be dots. If this is the case and all block
** characters are touching, we call the make_piece function. If not,
** the program exits.
*/

t_piece	*check_tetri(char *buf, char letter)
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
			error_exit();
		if (buf[i] == '\n' && (i % 5) != 4)
			error_exit();
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
		error_exit();
	return (NULL);
}
