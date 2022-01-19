/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:56:43 by abackman          #+#    #+#             */
/*   Updated: 2021/11/23 16:07:29 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(const char *s)
{
	size_t			i;
	unsigned char	ch;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		ch = (unsigned char)s[i];
		write(1, &ch, 1);
		i++;
	}
	write(1, "\n", 1);
}
