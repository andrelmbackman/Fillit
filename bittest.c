/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bittest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:32:01 by abackman          #+#    #+#             */
/*   Updated: 2022/01/13 16:49:41 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*)ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main(int argv, char* argc[])
{
	char str[16] = "...#...#...#...#";
	int	i;
	uint64_t bit;

	i = 64;
	bit = 0;
	printBits(sizeof(bit), &bit);
	while (i >= 0)
	{
		if (str[i] == '#')
			bit |= 1 << i;
		i--;
	}
	printBits(sizeof(bit), &bit);
	bit |= 1L << 31;
	printBits(sizeof(bit), &bit);
	return 0;
}