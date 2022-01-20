/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:04:57 by abackman          #+#    #+#             */
/*   Updated: 2022/01/19 13:50:26 by acamaras         ###   ########.fr       */
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
	size--;
	while (size >= 0)
	{
		ft_memdel((void **)&(map->map[size]));
		size--;
	}
	ft_memdel((void **)&(map->map));
	ft_memdel((void **)&map);
}

/*
** Sets the given character (letter) to the corresponding
** coordinates of the tetrimino (tetris) on the map.
*/

void	place_piece(t_map *map, t_piece *tetris, char letter)
{
	map->map[tetris->y_cord[0] + tetris->y_shift] \
	[tetris->x_cord[0] + tetris->x_shift] = letter;
	map->map[tetris->y_cord[1] + tetris->y_shift] \
	[tetris->x_cord[1] + tetris->x_shift] = letter;
	map->map[tetris->y_cord[2] + tetris->y_shift] \
	[tetris->x_cord[2] + tetris->x_shift] = letter;
	map->map[tetris->y_cord[3] + tetris->y_shift] \
	[tetris->x_cord[3] + tetris->x_shift] = letter;
}
