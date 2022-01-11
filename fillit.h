/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:25:49 by abackman          #+#    #+#             */
/*   Updated: 2022/01/11 13:28:23 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct t_tetrimino
{
	int				pos[8];
	char			letter;
	struct s_list	*next;
}	t_tetrimino;

typedef struct t_map
{
	int		size;
	char	**map;
}	t_map;

#endif
