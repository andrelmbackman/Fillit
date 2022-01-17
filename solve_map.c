/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:09:25 by abackman          #+#    #+#             */
/*   Updated: 2022/01/17 15:01:22 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
	if (!map)
		return ;
	while (size >= 0)
	{
		ft_memdel((void **)map->map[size]);
		size--;
	}
	free(map);
}

void	place_piece(t_map *map, t_piece *tetris)
{
	map->map[tetris->y_cord[0] + tetris->y_shift]\
	[tetris->x_cord[0] + tetris->x_shift] = tetris->letter;
	map->map[tetris->y_cord[1] + tetris->y_shift]\
	[tetris->x_cord[1] + tetris->x_shift] = tetris->letter;
	map->map[tetris->y_cord[2] + tetris->y_shift]\
	[tetris->x_cord[2] + tetris->x_shift] = tetris->letter;
	map->map[tetris->y_cord[3] + tetris->y_shift]\
	[tetris->x_cord[3] + tetris->x_shift] = tetris->letter;
}
/*
int	solver(t_map *map, t_piece *tetris, int size)
{
	while (check_y(map, tetris))
	{
		while (check_x(map, tetris))
		{
			if (check_place(map, tetris))
			{
				place_piece(map, tetris);
				if (solver(map, tetris->next, size));
					return (1);
			}
			tetris->x_shift++;
		}
		tetris->y_shift++;
	}
	return (0);
}
*/
void	solve_map(t_piece *tetris)
{
	int		mapsize;
	t_map	*map;

	mapsize = count_mapsize(tetris);
	map = create_map(mapsize);
	/*
	while (solver(map, tetris, mapsize) != 0)
	{
		free_map(map, mapsize);
		mapsize++;
		map = create_map(mapsize);
	}
	*/
	place_piece(map, tetris);
	print_map(map, map->size);
	free_map(map, map->size);
}
