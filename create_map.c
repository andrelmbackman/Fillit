/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:33 by abackman          #+#    #+#             */
/*   Updated: 2022/01/20 18:53:46 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** This is a helper function for the create_map function
** which allocates the correct size of the string based on
** the map's size. It basically fills the string with dots.
*/

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

/*
** This function gets the correct minimum size of the map we need to create
** based on the amount of tetriminos which we get by substacting 64
** (which in ASCII table stands for the character before 'A') from
** the last letter we arrived to when we were creating the tetrimino
** list (see function make_piecelist).
** mapsize is the total number of blocks and sqroot is the minimum
** height and width needed to fit those blocks.
*/

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

t_map	*create_map(int mapsize)
{
	t_map	*map;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->size = mapsize;
	map->map = (char **)ft_memalloc(mapsize * sizeof(char *));
	fill_dots(map, mapsize);
	return (map);
}
