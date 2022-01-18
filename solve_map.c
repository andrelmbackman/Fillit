/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:09:25 by abackman          #+#    #+#             */
/*   Updated: 2022/01/18 16:11:09 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void	print_map(t_map *map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putendl(map->map[i]);
		i++;
	}
}

void	free_map(t_map *map, int size)
{
	size--;
	while (size >= 0)
	{
		ft_memdel((void **)&(map->map[size]));
		size--;
	}
	ft_memdel((void **)&(map->map));
	ft_memdel((void **)&map);
}

void	place_piece(t_map *map, t_piece *tetris, char letter)
{
	map->map[tetris->y_cord[0] + tetris->y_shift]\
	[tetris->x_cord[0] + tetris->x_shift] = letter;
	map->map[tetris->y_cord[1] + tetris->y_shift]\
	[tetris->x_cord[1] + tetris->x_shift] = letter;
	map->map[tetris->y_cord[2] + tetris->y_shift]\
	[tetris->x_cord[2] + tetris->x_shift] = letter;
	map->map[tetris->y_cord[3] + tetris->y_shift]\
	[tetris->x_cord[3] + tetris->x_shift] = letter;
}

int	check_place(t_map *map, t_piece *tetris)
{
	if (map->map[tetris->y_cord[0] + tetris->y_shift]\
	[tetris->x_cord[0] + tetris->x_shift] == '.' &&\
	map->map[tetris->y_cord[1] + tetris->y_shift]\
	[tetris->x_cord[1] + tetris->x_shift] == '.' &&\
	map->map[tetris->y_cord[2] + tetris->y_shift]\
	[tetris->x_cord[2] + tetris->x_shift] == '.'&&\
	map->map[tetris->y_cord[3] + tetris->y_shift]\
	[tetris->x_cord[3] + tetris->x_shift] == '.')
		return (1);
	else
		return (0);
}

int	check_y(int size, t_piece *piece)
{
	if (piece->y_cord[0] + piece->y_shift < size &&\
	piece->y_cord[1] + piece->y_shift < size &&\
	piece->y_cord[2] + piece->y_shift < size &&\
	piece->y_cord[3] + piece->y_shift < size)
		return (1);
	else
		return (0);
}

int	check_x(int size, t_piece *piece)
{
	if (piece->x_cord[0] + piece->x_shift < size &&\
	piece->x_cord[1] + piece->x_shift < size &&\
	piece->x_cord[2] + piece->x_shift < size &&\
	piece->x_cord[3] + piece->x_shift < size)
		return (1);
	else
		return (0);
}

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

void	solve_map(t_piece *tetris)
{
	int		mapsize;
	t_map	*map;

	mapsize = count_mapsize(tetris);
	map = create_map(mapsize);
	while (!solver(map, tetris, mapsize))
	{
		free_map(map, mapsize);
		mapsize++;
		map = create_map(mapsize);
	}
	//place_piece(map, tetris);
	print_map(map, map->size);
	free_map(map, map->size);
	free_tetri(tetris);
}
