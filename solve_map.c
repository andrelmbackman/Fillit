/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:09:25 by abackman          #+#    #+#             */
/*   Updated: 2022/01/20 19:04:09 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Here we check if the places are dots, which means they are
** available. Tetris->y_cord[0-3] and tetris->x_cord[0-3] describe
** the coordinates for the 4 block pieces ('#').
** y_shift and x_shift are integers corresponding to how many steps
** they have been moved from the top-left corner.
** If it can be placed the function returns 1.
*/

int	check_place(t_map *map, t_piece *tetris)
{
	if (map->map[tetris->y_cord[0] + tetris->y_shift] \
	[tetris->x_cord[0] + tetris->x_shift] == '.' && \
	map->map[tetris->y_cord[1] + tetris->y_shift] \
	[tetris->x_cord[1] + tetris->x_shift] == '.' && \
	map->map[tetris->y_cord[2] + tetris->y_shift] \
	[tetris->x_cord[2] + tetris->x_shift] == '.' && \
	map->map[tetris->y_cord[3] + tetris->y_shift] \
	[tetris->x_cord[3] + tetris->x_shift] == '.')
		return (1);
	else
		return (0);
}

/*
** Here we check if the piece is in bounds on the y-axis.
** We check that the coordinates + the amount of times
** it has been shifted is smaller than the map's size.
*/

int	check_y(int size, t_piece *piece)
{
	if (piece->y_cord[0] + piece->y_shift < size && \
	piece->y_cord[1] + piece->y_shift < size && \
	piece->y_cord[2] + piece->y_shift < size && \
	piece->y_cord[3] + piece->y_shift < size)
		return (1);
	else
		return (0);
}

/*
** Here we check if the piece is in bounds on the x-axis. 
** We check that the coordinates + the amount of times
** it has been shifted is smaller than the map's size.
*/

int	check_x(int size, t_piece *piece)
{
	if (piece->x_cord[0] + piece->x_shift < size && \
	piece->x_cord[1] + piece->x_shift < size && \
	piece->x_cord[2] + piece->x_shift < size && \
	piece->x_cord[3] + piece->x_shift < size)
		return (1);
	else
		return (0);
}

/*
** Recursive backtracking solver function. The starting point is
** that the tetrimino is in the top-left corner. We then check if
** it is in bounds on the y-axis and the x-axis. If it is, we check
** if the piece can be placed. If it can, we place it and check if
** the next piece can be placed within the map. If the next piece
** can't be placed within the map, we "remove" the previous piece,
** shift it and try again. If it can't find a place within bounds
** the function returns 0.
*/

int	solver(t_map *map, t_piece *tetris, int size)
{
	if (!tetris)
		return (1);
	tetris->y_shift = 0;
	tetris->x_shift = 0;
	while (check_y(map->size, tetris))
	{
		while (check_x(map->size, tetris))
		{
			if (check_place(map, tetris))
			{
				place_piece(map, tetris, tetris->letter);
				if (solver(map, tetris->next, size))
					return (1);
				else
					place_piece(map, tetris, '.');
			}
			tetris->x_shift++;
		}
		tetris->x_shift = 0;
		tetris->y_shift++;
	}
	return (0);
}

/*
** solve_map declares the map, calls the function to calculate
** the minimum map size we need and creates the map.
** The solver function is then called in a while loop. If the map size
** is insufficient it returns 0, we then free the map, increase the
** mapsize and create a new one. When the solution is found the map
** is printed and freed. The list of tetriminos is also freed.
*/

void	solve_map(t_piece *tetris)
{
	int		mapsize;
	t_map	*map;

	mapsize = count_mapsize(tetris);
	map = create_map(mapsize);
	if (!map)
		error_exit();
	while (!solver(map, tetris, mapsize))
	{
		free_map(map, mapsize);
		mapsize++;
		map = create_map(mapsize);
		if (!map)
			error_exit();
	}
	print_map(map, map->size);
	free_map(map, map->size);
	free_tetri(tetris);
}
