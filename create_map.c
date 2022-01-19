/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:33 by abackman          #+#    #+#             */
/*   Updated: 2022/01/19 13:32:04 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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