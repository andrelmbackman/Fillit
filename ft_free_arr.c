/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:56:43 by abackman          #+#    #+#             */
/*   Updated: 2022/02/09 15:00:14 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_arr(char **str, size_t size)
{
	size_t	i;

	i = 0;
	while (i <= size)
	{
		ft_bzero(str[size], ft_strlen(str[size]));
		free(str[size]);
		i++;
	}
	free(str);
	return (NULL);
}
