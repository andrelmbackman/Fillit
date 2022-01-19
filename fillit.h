/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:49 by abackman          #+#    #+#             */
/*   Updated: 2022/01/19 13:06:16 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>

typedef struct s_piece
{
	char			piece[16];
	int				x_cord[4];
	int				y_cord[4];
	int				x_shift;
	int				y_shift;
	int				count;
	char			letter;
	char			last_letter;
	struct s_piece	*next;
}	t_piece;

typedef struct s_map
{
	int		size;
	char	**map;
}	t_map;

void	solve_map(t_piece *tetris);
void	print_map(t_map *map, int size);
void	free_map(t_map *map, int size);
void	place_piece(t_map *map, t_piece *tetris, char letter);
void	error_exit(int fd);
int		count_mapsize(t_piece *pieces);
t_map	*create_map(int sqroot);
t_piece	*free_tetri(t_piece *tetris);
t_piece	*check_tetri(char *buf, char letter, int fd);

#endif
